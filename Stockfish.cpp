#include "Stockfish.h"
#include <algorithm>
#include "easylogging++.h"

Stockfish::Stockfish()
{
	createStockfishProcess();
}

bool Stockfish::createStockfishProcess()
{
    bool success = false;

    // Set up the _security attributes
    _security.nLength = sizeof(SECURITY_ATTRIBUTES);
    _security.bInheritHandle = TRUE;
    _security.lpSecurityDescriptor = NULL;


    // Zero the memory for startup info and process info
    ZeroMemory(&_startupInfo, sizeof(_startupInfo));
    _startupInfo.cb = sizeof(_startupInfo);
    ZeroMemory(&_processInfo, sizeof(_processInfo));

    // Create the pipes

    // Create pipe for Stockfish standard input
    if (!CreatePipe(&_hInRead, &_hInWrite, &_security, 0))
    {
        std::cout << "Standard input pipe creation failed!\n";
        return success;
    }

    // Create pipe for Stockfish standard output
    if (!CreatePipe(&_hOutRead, &_hOutWrite, &_security, 0))
    {
        std::cout << "Standard output pipe creation failed!\n";
        return success;
    }

    // Set the handles for startup info
    _startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    _startupInfo.hStdOutput = _hOutWrite;
    _startupInfo.hStdInput = _hInRead;
    _startupInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Create the Stockfish process using the pipes.
    if (!CreateProcess(
        (LPCWSTR)L"stockfish.exe",  // Path to stockfish
        (LPTSTR)L"",                // Using the command line
        NULL,                       // Process handle not inheritable
        NULL,                       // Thread handle not inheritable
        TRUE,                       // Set handle inheritance to TRUE (!IMPORTANT!)
        CREATE_NO_WINDOW,                          // No creation flags
        NULL,                       // Use parent environment blocks
        NULL,                       // Use parent starting directory
        &_startupInfo,               // Pointer to the startup info structure that contains the handles to use
        &_processInfo))              // Pointer to the process info struct, filled by reference with the results of CreateProcess
    {
        std::cout << "Process creation failed!";
        success = false;
        return success;
    }
    else
    {
        success = true;
    }

    return success;
}

bool Stockfish::newGameStockfish(std::string fen)
{
    bool newGame = false;

    // Clear the previous output, if any
    _fishOutput.clear();

    // Send the UCI command to stockfish
    commandStockfish("uci");

    // Read the response.
    _fishOutput = readStockfishOutput();

    // Determine if the response contains "uciok", signifying that the engine is ready for UCI input.
    if (std::find(_fishOutput.begin(), _fishOutput.end(), "uciok\r") == _fishOutput.end())
    {
        LOG(DEBUG) << "uciok message not found! Stockfish could not create a new game.";
        return newGame;
    }
    else
    {
        for (std::string str : _fishOutput)
        {
            LOG(TRACE) << "Stockfish: " << str;
        }
    }

    // Check for the "readyok" from Stockfish
    while (!isStockfishReady())
    {
        LOG(DEBUG) << "Stockfish not ready!";
        Sleep(500);
    }
    
    commandStockfish("ucinewgame");
    Sleep(500);

    // Check for the "readyok" from Stockfish
    while (!isStockfishReady())
    {
        LOG(DEBUG) << "Stockfish not ready!";
        Sleep(500);
    }

    _fishOutput.clear();

    commandStockfish("position startpos");
    commandStockfish(fen);

    // Check for the "readyok" from Stockfish
    while (!isStockfishReady())
    {
        LOG(DEBUG) << "Stockfish not ready!";
        Sleep(500);
    }

    LOG(TRACE) << "New Stockfish game created, position set!";

    newGame = true;
    return newGame;

}

void Stockfish::commandStockfish(std::string command)
{
    DWORD bytesWritten = 0;
    command += '\n';
    if (!WriteFile(_hInWrite, command.c_str(), command.length(), &bytesWritten, NULL))
    {
        LOG(DEBUG) << "Command not sent!";
    }
}

bool Stockfish::isStockfishReady()
{
    bool ready = false;
    _fishOutput.clear();
    commandStockfish("isready");
    _fishOutput = readStockfishOutput();

    // Determine if the response contains "uciok", signifying that the engine is ready.
    if (std::find(_fishOutput.begin(), _fishOutput.end(), "readyok\r") == _fishOutput.end())
    {
        LOG(DEBUG) << "Stockfish not ready!";
        ready = false;
        return ready;
    }
    else
    {
        LOG(TRACE) << "Stockfish is ready, OK!";
        ready = true;
        return ready;
    }

}

std::vector<std::string> Stockfish::readStockfishOutput(DWORD delay)
{
    // Waits for output from Stockfish. Probably could implement some sort of Peek here instead of a naive Wait
    Sleep(delay);
    LOG(TRACE) << "Reading from Stockfish...";

    std::vector<std::string> output;
    DWORD bytesRead = 0;
    char buffer[1024 * 8];

    for (;;)
    {
        // Check if Read operation was successful
        if (!ReadFile(_hOutRead, buffer, sizeof(buffer), &bytesRead, NULL))
        {
            LOG(ERROR) << "Failed to read from Stockfish! Bytes read: " << bytesRead;
            DWORD errorCode = GetLastError();
            if (errorCode == ERROR_BROKEN_PIPE)
            {
                printf("Pipe was closed!\n");
            }
            else
            {
                LOG(ERROR) << "Error occurred while reading from the pipe: " << errorCode;
            }
            break;
        }

        // Set up the console buffer stream and push any responses to the vector
        std::stringstream bufferStream(std::string(buffer, bytesRead));
        std::string line;
        while (std::getline(bufferStream, line))
        {
            output.push_back(line);
        }

        // Flush the std output buffer
        fflush(stdout);
        break;

    }

    return output;

}

bool Stockfish::waitForBestMove()
{
    bool move = false;
    _fishOutput.clear();

    std::vector<std::string>::iterator itr;

    while (!move)
    {
        _fishOutput = readStockfishOutput(500);
        itr = std::find_if(_fishOutput.begin(), _fishOutput.end(), [](const std::string& str) {
            return str.find("bestmove") != std::string::npos; 
            });
        if (itr != _fishOutput.end())
        {
            // Put the "bestmove" string into Stockfish's _bestMove member variable.
            _bestMove = *itr;
            move = true;
        }
        else
        {
            move = false;
            continue;
        }
    }

    return move;

}