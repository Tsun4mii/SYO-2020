@ECHO OFF
ml /c /coff /Zi "D:\User\Desktop\CourseWork\SYO-2020\Generation\Generation\Gen.asm"
link /OPT:NOREF /DEBUG "D:\User\Desktop\CourseWork\SYO-2020\Debug\Gen.obj" "D:\User\Desktop\CourseWork\SYO-2020\Generation\Debug\GenLib.lib" /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call D:\User\Desktop\CourseWork\SYO-2020\Debug\Gen.exe