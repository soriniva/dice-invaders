FILES          = src/SpaceInvaders.cpp src/Engine.cpp src/Player.cpp src/Weapon.cpp src/Utils.cpp src/Alien.cpp src/AlienPack.cpp
EXECUTABLE     = SpaceInvaders.exe
CFLAGS         = /nologo /Z7 /W4 /WX /Fe$(EXECUTABLE) /D_HAS_EXCEPTIONS=0
CFLAGS_RELEASE = $(CFLAGS) /Ox /MT /DNDEBUG
CFLAGS_DEBUG   = $(CFLAGS) /Od /MTd /D_DEBUG
CC             = cl.exe
DEVENV         = devenv.exe

debug: dummy
	$(CC) $(CFLAGS_DEBUG) $(FILES)

release: dummy
	$(CC) $(CFLAGS_RELEASE) $(FILES)

dev: debug
	$(DEVENV) $(EXECUTABLE)

clean: dummy
	-@del $(EXECUTABLE)
	-@del *.obj
	-@del *.pdb
	-@del *.ilk

dummy:


