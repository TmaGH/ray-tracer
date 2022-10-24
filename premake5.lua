workspace "RayTracer"
  configurations { "Test", "Debug", "Release" }
  platforms { "Windows" }

project "RayTracer"
  location "RayTracer"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  architecture "x86_64"

  targetdir "bin/%{cfg.buildcfg}-%{cfg.platform}/%{prj.name}"
  objdir "bin-obj/%{cfg.buildcfg}-%{cfg.platform}/%{prj.name}"

  includedirs { "%{cfg.location}/src", "%{cfg.Location}/vendor/spdlog/include" }

  files { "%{cfg.location}/src/**.h", "%{cfg.location}/src/**.cpp" }
  
  filter "system:windows"
    defines { "EG_PLATFORM_WINDOWS" }
    cppdialect "C++20"
    systemversion "latest"

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
    removefiles { "%{cfg.location}/src/**.test.cpp" }

  filter "configurations:Release"
    defines { "NDEBUG", "RELEASE" }
    optimize "On"
    removefiles { "%{cfg.location}/src/**.test.cpp" }
  
  filter "configurations:Test"
    defines { "TEST" }
    optimize "On"
    includedirs { "%{cfg.location}/vendor/catch2" }