Write-Output "copying DLLs..."

Copy-Item '../cmake-build-release-visual-studio/libs/dpp/dpp.dll' '../cmake-build-release-visual-studio/dpp.dll'
Copy-Item '../cmake-build-release-visual-studio/libs/dpp/libcrypto-1_1-x64.dll' '../cmake-build-release-visual-studio/libcrypto-1_1-x64.dll'
Copy-Item '../cmake-build-release-visual-studio/libs/dpp/libsodium.dll' '../cmake-build-release-visual-studio/libsodium.dll'
Copy-Item '../cmake-build-release-visual-studio/libs/dpp/libssl-1_1-x64.dll' '../cmake-build-release-visual-studio/libssl-1_1-x64.dll'
Copy-Item '../cmake-build-release-visual-studio/libs/dpp/opus.dll' '../cmake-build-release-visual-studio/opus.dll'

Copy-Item '../cmake-build-release-visual-studio/libs/spdlog/spdlog.dll' '../cmake-build-release-visual-studio/spdlog.dll'

Write-Output "copied DLLs successfully"