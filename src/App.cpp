#include "../include/App.hpp"
#include "../include/ImageViewer.hpp"
#include <iostream>
#include <windows.h>

const std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> App::parseArguments(const int argc, char* argv[])
{
    if (argc != 2)
        throw std::runtime_error("Invalid number of arguments!");
    const std::experimental::filesystem::path executable_path = std::string(argv[0]);
    const std::experimental::filesystem::path resource_folder = executable_path.parent_path();
    const std::experimental::filesystem::path file_path = std::string(argv[1]);
    return { resource_folder, file_path };
}

int App::run(const int argc, char* argv[])
{
    try {
        std::pair<std::experimental::filesystem::path, std::experimental::filesystem::path> arguments = this->parseArguments(argc, argv);
        const std::experimental::filesystem::path resource_folder = arguments.first;
        std::experimental::filesystem::path file_path = arguments.second;
        ImageViewer viewer(resource_folder);
        while (!do_exit) {
            switch (viewer.getStatus()) {
            case ImageViewerStatus::RunFastMode:
                file_path = viewer.runFastMode(file_path).second;
                break;
            case ImageViewerStatus::RunPolishedMode:
                file_path = viewer.runPolishedMode(file_path).second;
                break;
            case ImageViewerStatus::LeftOk:
                this->do_exit = true;
                break;
            case ImageViewerStatus::Error:
                this->exit_code = 1;
                this->do_exit = true;
                break;
            case ImageViewerStatus::OngoingTask:
                std::cout << "OngoingTask: Something was not expected to happen" << std::endl;
                throw;
            case ImageViewerStatus::NothingAssigned:
                file_path = viewer.runFastMode(file_path).second;
                break;
            }
        }
        return this->exit_code;
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        MessageBoxA(
            NULL,
            error.what(),
            "Error",
            MB_OK | MB_ICONERROR);
        return 1;
    }
}

App::App()
    : do_exit(false)
    , exit_code(0)
{
}
