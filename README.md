# Dll Export Compare

A simple tool for comparing DLL exports to find exports that are missing in either of the compared DLLs

Since this is a development tool, I didn't set up a CI pipeline, so you will need to clone the repo and compile the project yourself.

## Usage:
Input in terminal:
`DllExportCompare.exe "D:\steam_api_o.dll" "D:\steam_api.dll"`

Output:
```
[stdout] [info] DLL Export Compare
[stdout] [info] No unique exports are present in the first DLL (D:\steam_api_o.dll)
[stdout] [info] DLL Exports present only in the second DLL (D:\steam_api.dll)
[stdout] [info]   * CAddUGCDependencyResult_t_RemoveCallResult
[stdout] [info]   * CAddUGCDependencyResult_t_SetCallResult
```