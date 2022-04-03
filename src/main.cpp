#include "koalabox/koalabox.hpp"
#include "koalabox/util/util.hpp"
#include "koalabox/win_util/win_util.hpp"
#include "koalabox/loader/loader.hpp"
#include "spdlog/sinks/stdout_sinks.h"

using namespace koalabox;

/**
 * Args <br>
 * 0: program name <br>
 * 1: dll #1 path <br>
 * 2: dll #2 path <br>
 */
int wmain(const int argc, const wchar_t* argv[]) {
    logger = spdlog::stdout_logger_st("stdout");
    logger->flush_on(spdlog::level::trace);

    logger->info("DLL Export Compare");

    if (argc != 3) {
        logger->error("Invalid number of arguments. Expected 2. Got: {}", argc - 1);
        exit(1);
    }

    const auto dll_path_1 = Path(argv[1]);
    const auto dll_path_2 = Path(argv[2]);

    for (const auto& path: Vector<Path>{ dll_path_1, dll_path_2 }) {
        if (not exists(path)) {
            util::panic("Non-existent DLL path: {}", path.string());
        }
    }

    const auto library_1 = win_util::load_library(dll_path_1);
    const auto library_2 = win_util::load_library(dll_path_2);

    const auto dll_exports_1 = loader::get_export_map(library_1);
    const auto dll_exports_2 = loader::get_export_map(library_2);

    Set<String> exports_only_in_1;
    Set<String> exports_only_in_2;

    for (const auto&[key, _]: dll_exports_1) {
        if (not dll_exports_2.contains(key)) {
            exports_only_in_1.insert(key);
        }
    }

    for (const auto&[key, _]: dll_exports_2) {
        if (not dll_exports_1.contains(key)) {
            exports_only_in_2.insert(key);
        }
    }

    if (exports_only_in_1.empty()) {
        logger->info("No unique exports are present in the first DLL ({})", dll_path_1.string());
    } else {
        logger->info("DLL Exports present only in the first DLL ({})", dll_path_1.string());
        for (const auto& function: exports_only_in_1) {
            logger->info("  * {}", function);
        }
    }

    if (exports_only_in_2.empty()) {
        logger->info("No unique exports are present in the second DLL ({})", dll_path_2.string());
    } else {
        logger->info("DLL Exports present only in the second DLL ({})", dll_path_2.string());
        for (const auto& function: exports_only_in_2) {
            logger->info("  * {}", function);
        }
    }

    return 0;
}
