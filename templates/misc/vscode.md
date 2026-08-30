Run -> Add configuration... -> in launch.json:

    "program": "${fileDirname}/${fileBasenameNoExtension}",
    "preLaunchTask": "C/C++: g++ build active file",
