# 🧀 hsr-cheese

** Best Cheese and Goon Material.

### 🚀 Project Status
| Platform | Status |
| :--- | :--- |
| `Windows` | ![Windows Build](https://github.com/monakaibrahim-cmyk/hsr-cheese/actions/workflows/windows.yml/badge.svg?branch=development) |
| `Linux` | ![Linux Build](https://github.com/monakaibrahim-cmyk/hsr-cheese/actions/workflows/linux.yml/badge.svg?branch=development) |

## ⚙️ Build Instructions
* **CMake:** Version 3.20 or higher.
* **Compiler:** C++20 compatible (MSVC 2022, GCC 10+, or MinGW-w64).
* **Git:** Required for submodule management.
* **Dependencies:** DirectX SDK (D3D11/DXGI)

### Compilation Steps

1. **Clone the Repository** (including submodules):
	```bash
	git clone --recursive https://github.com/monakaibrahim-cmyk/hsr-cheese.git
	cd hsr-cheese
	```

2. Configure the Project:
	```bash
	cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	```	

3. Build the Project:
	```bash
	cmake --build build --config Debug
	```

The resulting library (`PipsiHSR.dll`) will be located in the `out/build/x64-Debug` directory.

## 💎 Credits
[@Z4ee](https://github.com/Z4ee) - for the goon materials.

## ⚖️ Disclaimer
This project is for educational and research purposes only. The developers are not responsible for any account actions taken by game providers. Use at your own discretion.
