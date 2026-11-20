import os, sys, re, shutil
import subprocess

rootDir = os.path.dirname(__file__)
if not rootDir:
    rootDir = os.path.abspath(".")
rootDir = os.path.abspath(os.path.join(rootDir, "../NativeImpl/LunaHook"))

if len(sys.argv) > 1 and sys.argv[1] == "merge":
    # Artifacts from the build jobs are downloaded to build/<arch>/,
    # each holding that arch's builds/Release_<target> output.
    os.chdir(rootDir)
    os.makedirs("builds", exist_ok=True)

    targetdir = "../build/Release"
    for arch in ("x86", "x64"):
        shutil.copytree(
            f"build/{arch}/Release_win7",
            targetdir,
            dirs_exist_ok=True,
            ignore=shutil.ignore_patterns("*.pdb", "*.ilk", "*.exp", "*.lib"),
        )

    target = "builds/Release.zip"
    subprocess.run(
        [r"C:\Program Files\7-Zip\7z.exe", "a", "-m0=Deflate", "-mx9", target, targetdir],
        check=True,
    )
    exit()

print(sys.version)
print(__file__)
print(rootDir)

os.chdir(rootDir)
if sys.argv[1] == "plugin":
    bits = sys.argv[2]
    with open("buildplugin.bat", "w") as ff:
        if bits == "32":
            ff.write(
                rf"""
cmake -DBUILD_CORE=OFF -DUSESYSQTPATH=1 -DBUILD_PLUGIN=ON ./CMakeLists.txt -G "Visual Studio 18 2026" -A win32 -T host=x86 -B ./build/plugin32
cmake --build ./build/plugin32 --config Release --target ALL_BUILD -j {os.cpu_count()}
"""
            )
        else:
            ff.write(
                rf"""
cmake -DBUILD_CORE=OFF -DUSESYSQTPATH=1 -DBUILD_PLUGIN=ON ./CMakeLists.txt -G "Visual Studio 18 2026" -A x64 -T host=x64 -B ./build/plugin64
cmake --build ./build/plugin64 --config Release --target ALL_BUILD -j {os.cpu_count()}
"""
            )
    os.system(f"cmd /c buildplugin.bat")
elif sys.argv[1] == "build":
    arch = sys.argv[2]
    core = int(sys.argv[3])
    target = sys.argv[4]

    archA = ("win32", "x64")[arch == "x64"]
    vsver = "Visual Studio 18 2026"
    # VS 2026 has no v141_xp toolset; XP support comes from YY-Thunks (see build_lunatranslator.py).
    Tool = f"host={arch}"
    # WIN10ABOVE defaults to ON in CMakeLists.txt, so it must be turned off explicitly for win7/winxp.
    config = {
        "win10": "-DWIN10ABOVE=ON",
        "win7": "-DWIN10ABOVE=OFF",
        "winxp": "-DWINXP=ON -DWIN10ABOVE=OFF",
    }[target]
    if not core:
        config += " -DBUILD_GUI=ON "

    subprocess.run(
        f'cmake {config} ./CMakeLists.txt -G "{vsver}" -A {archA} -T {Tool} -B ./build/{arch}_{target}',
        check=True,
    )
    subprocess.run(
        f"cmake --build ./build/{arch}_{target} --config Release --target ALL_BUILD -j {os.cpu_count()}",
        check=True,
    )
