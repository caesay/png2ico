#include <fstream>
#include <iostream>
// #include <memory>
#include <filesystem>
#include <string>
#include "flags.h"
#include "glob.h"

#if _WIN32
#include "lib/x86/FreeImage.h"
#pragma comment(lib, "lib/x86/FreeImage.lib")
#endif

#if _WIN64
#include "lib/x64/FreeImage.h"
#pragma comment(lib, "lib/x64/FreeImage.lib")
#endif

using namespace std;
namespace fs = std::filesystem;

void printfree(FREE_IMAGE_FORMAT fif, const char* msg)
{
    cout << msg << std::endl;
}

int main(int argc, char* argv[])
{
    vector<string> files{};
    const flags::args args(argc, argv);

    auto outputFile = args.get<string>("o", "out.ico");

    auto& sv = args.positional();
    for (const auto& file : sv)
    {
        auto dir = fs::path(file).parent_path();
        const string f(file);
        glob::glob gl(f);
        while (gl) {

            fs::path child = dir / gl.current_match();
            files.push_back(child.generic_string());
            cout << "Loading: " << child << std::endl;
            gl.next();
        }
    }

    FreeImage_SetOutputMessage(printfree);

    FIMULTIBITMAP* ico = FreeImage_OpenMultiBitmap(FIF_ICO, outputFile.c_str(), TRUE, FALSE);

    for (const auto& file : files)
    {
        FIBITMAP* page = FreeImage_Load(FIF_PNG, file.c_str());
        FreeImage_AppendPage(ico, page);
        FreeImage_Unload(page);
    }

    FreeImage_CloseMultiBitmap(ico);
}
