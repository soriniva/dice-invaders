FILES          = SpaceInvaders.cpp Engine.cpp Player.cpp Weapon.cpp Utils.cpp Alien.cpp AlienPack.cpp
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


