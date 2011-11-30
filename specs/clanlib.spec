#
# spec file for package clanlib
#
# Copyright (c) 2011 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


%define clan_ver 2.3

Name:           clanlib
Version:        2.3.3
Release:        23.1.fc16
License:        Other uncritical OpenSource License
Summary:        A Portable Interface for Writing Games
URL:            http://www.clanlib.org/
Group:          System/Libraries
Source:         ClanLib-%{version}.tgz
BuildRequires:  doxygen
BuildRequires:  fdupes
BuildRequires:  fontconfig-devel
BuildRequires:  gcc-c++
BuildRequires:  libjpeg-devel
BuildRequires:  libmikmod-devel
BuildRequires:  libogg-devel
BuildRequires:  libpng-devel
BuildRequires:  libstdc++-devel
BuildRequires:  libvorbis-devel
BuildRequires:  libxslt
BuildRequires:  pcre-devel
BuildRequires:  zlib-devel
BuildRequires:  dos2unix
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
ClanLib delivers a platform-independent interface for writing games.

%package        devel
Summary:        A portable interface for writing games
Group:          Development/Libraries/X11
Requires:       %{name} = %{version}
Requires:       libstdc++-devel

%description     devel
ClanLib delivers a platform independent interface to write games with.

%package        doc
Summary:        A Portable Interface for Writing Games
Group:          Documentation/HTML
Requires:       %{name} = %{version}
%if 0%{?suse_version} >= 1120
BuildArch:      noarch
%endif

%description     doc
ClanLib delivers a platform-independent interface for writing games.

%package        examples
Summary:        A Portable Interface for Writing Games
Group:          Documentation/Other
Requires:       %{name} = %{version}
Requires:       %{name}-devel = %{version}
%if 0%{?suse_version} >= 1120
BuildArch:      noarch
%endif

%description    examples
ClanLib delivers a platform-independent interface for writing games.

%prep
%setup -q -n ClanLib-%{version}
find Examples -name \*.sln -o -name \*.vcproj -o -name \*.vcxproj\* | xargs rm -f
dos2unix Examples/Game/SpritesRTS/resources.xml Examples/Database/SQL/Database/create_database.sql \
	Examples/3D/Chess3D/Resources/Sponza/readme.txt Examples/3D/Chess3D/Resources/skybox_fragment.glsl \
	Examples/Game/Pacman/pacman.xml Examples/3D/Chess3D/Resources/skybox_vertex.glsl \
	Examples/Game/TileMap/README.txt \
	Examples/3D/Clan3D/Resources/teapot.dae \
	Examples/Game/TileMap/Resources/tileset.txt

%build
export CFLAGS="%{optflags}"
export CXXFLAGS="$CFLAGS"
%ifarch %ix86
%configure --with-pic --disable-static --enable-asm386 --enable-docs
%else
%configure --with-pic --disable-static --disable-asm386 --enable-docs
%endif
make %{?_smp_mflags}

%install
%makeinstall
rm -f %{buildroot}%{_libdir}/*.la
mkdir -p %{buildroot}%{_datadir}/doc/clanlib-%{clan_ver}
cp -a Examples %{buildroot}%{_datadir}/doc/clanlib-%{clan_ver}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%doc COPYING CREDITS README
%{_libdir}/libclan*.so.*

%files devel
%defattr(-, root, root)
%doc CODING_STYLE PATCHES
%{_includedir}/*
%{_libdir}/pkgconfig/*
%{_libdir}/libclan*.so

%files doc
%defattr(-, root, root)
%{_datadir}/doc/clanlib-%{clan_ver}/
%exclude %{_datadir}/doc/clanlib-%{clan_ver}/Examples

%files examples
%defattr(-, root, root)
%{_datadir}/doc/clanlib-%{clan_ver}/Examples

%changelog
* Wed Nov 16 2011 jengelh@medozas.de
- Remove redundant/unwanted tags/section (cf. specfile guidelines)
* Wed Nov 16 2011 jreidinger@suse.com
- Update to version 2.3.3:
  * this is major version update (from 2.2.9 to 2.3.3).
  * complete list of changes is available here:
  http://clanlib.org/wiki/BreakingChanges and
  here http://clanlib.org/wiki/ClanLib_2.3.3_Release_Notes
* Sat Jul  2 2011 jengelh@medozas.de
- Use %%_smp_mflags for parallel building
- Strip %%clean section (not needed on BS)
* Thu Jun 16 2011 pth@suse.de
- Fix file list.
- Fix copying of Examples.
- Convert line endings in some text files.
* Sat Jun 11 2011 vlado.paskov@gmail.com
- Update to version 2.2.9:
  * this is major version update (from 2.1.1 to 2.2.9).
  * complete list of changes is available here:
  http://clanlib.org/wiki/BreakingChanges and
  here http://clanlib.org/wiki/ClanLib_2.2.9_Release_Notes
* Sat Mar 13 2010 dimstar@opensuse.org
- Update to version 2.1.1:
  + See UpGRADE.txt for changes.
* Tue Feb  9 2010 prusnak@suse.cz
- build -doc and -examples subpackages as noarch
* Wed Aug  5 2009 prusnak@suse.cz
- updated to 2.0.3
  * new display target: GL1 (works on pre OpenGL 2.0 cards)
- removed obsoleted patch:
  * includes.patch (mainline)
* Tue Jul  7 2009 prusnak@suse.cz
- added COPYING.GPLv2 to examples subpackage [bnc#519487]
* Tue May 19 2009 prusnak@suse.cz
- updated to 2.0.2
  * New (revived) display target: SDL
  * New example: GUICustomComponent (game-gui)
  * New example: PostProcessing (using shaders)
- fixed missing includes (includes.patch)
- removed obsoleted patches:
  * used-twice.patch (mainline)
* Thu Apr 30 2009 prusnak@suse.cz
- updated to 2.0.1
  * changes too numerous to list
- fixed the same variable used twice in expression (used-twice.patch)
- removed obsoleted patches
  * endian.patch (not needed anymore)
  * delete.patch (mainline)
  * includes.patch
* Sun Mar 29 2009 crrodriguez@suse.de
- fix build with GCC 44
* Mon Nov 10 2008 prusnak@suse.cz
- fix wrong delete usage (delete.patch) [bnc#443368]
* Wed Mar 19 2008 prusnak@suse.cz
- updated to 0.8.1
  * GUI: CL_InputBox improved, supports system-wide cut-and-paste
  * GUI: RichEdit class added, currently only a very basic html style viewer
  * Global: CL_Clipboard added
  * ClanDisplay: .bmp loading support added
  * ClanSound: ALSA support added
  - Loads of bugs fixed
- removed obsolete patch:
  * clvoid.patch (included in update)
* Thu Oct 18 2007 prusnak@suse.cz
- fixed missing includes (includes.patch)
- changed Xalan-c to libxslt (xsltproc) in BuildRequires to build docs
* Tue Oct 16 2007 prusnak@suse.cz
- updated to 0.8.0
  * ,major changes, replaces legacy 0.6.5 release
  * see NEWS for more details
- added patches
  * clvoid.patch - replace CLvoid with void
  * endian.patch - enable endian check in configure.ac
- dropped obsolete patches
  * assert.patch
  * byteorder.patch
  * cast-warn.patch
  * DirectFB.patch
  * destdir.patch
  * docu.patch
  * fixes.patch
  * gcc41.patch
  * noexec.patch
  * show_commands.patch
  * std_c++.patch
* Wed May 23 2007 ro@suse.de
- added ldconfig to postscript
* Wed Apr 11 2007 sbrabec@suse.cz
- Require just created libmikmod-devel instead of libmikmod.
* Wed Feb  7 2007 ro@suse.de
- do not build as root
* Mon Dec 11 2006 meissner@suse.de
- mark up assembler as needing no executable stack.
* Mon Oct 16 2006 ro@suse.de
- use DirectFB-devel in BuildRequires
- add DirectFB-devel to require-list in devel package
* Thu Jul 13 2006 nadvornik@suse.cz
- fixed compile with new directfb
* Mon Jan 30 2006 nadvornik@suse.cz
- cleared setgid on source archive files
* Fri Jan 27 2006 nadvornik@suse.cz
- fixed Requires of devel subpackage
* Wed Jan 25 2006 mls@suse.de
- converted neededforbuild to BuildRequires
* Tue Nov 29 2005 meissner@suse.de
- fno-strict-aliasing.
* Mon Oct 17 2005 meissner@suse.de
- fixed gcc41 C++ problems.
* Mon Feb 28 2005 meissner@suse.de
- Fixed gcc4 C++ problems.
* Wed Jul 21 2004 schwab@suse.de
- Fix inappropriate mixing of signed and unsigned.
- Fix missing shifts.
* Wed Jul 21 2004 schwab@suse.de
- Fix stupid endian bug.
* Wed Jan 14 2004 ro@suse.de
- build with current DirectFB
* Wed Aug 27 2003 nadvornik@suse.cz
- do not package static libraries
* Thu Aug 14 2003 nadvornik@suse.cz
- fixed cast warnings
* Mon May 19 2003 ro@suse.de
- add static libs to devel subpackage
- remove .cvsignore files from package
* Tue Feb 25 2003 aj@suse.de
- Include missing assert.
* Fri Feb  7 2003 mcihar@suse.cz
- updated to 0.6.5:
  - DirectFB updates.
  - Misc minor bug fixes.
- compiled with joystick support
* Fri Feb  7 2003 ro@suse.de
- DirectFB-0.9.16 changed DSPF_RGB15 to DSPF_ARGB1555
* Mon Aug 26 2002 nadvornik@suse.cz
- fixed mode of doc files
* Fri Jul  5 2002 kukuk@suse.de
- Use %%ix86 macro
* Thu Jul  4 2002 ro@suse.de
- fix for libpng (add -lz)
* Mon Jun 17 2002 meissner@suse.de
- also run suse_update_config so we get a new and fresh config.guess.
* Fri Jun  7 2002 ro@suse.de
- use latest snapshot from 0.6 branch to compile with
  DirectFB 0.9.11
* Sat Jun  1 2002 ro@suse.de
- changed neededforbuild <libmikmo> to <libmikmod>
* Mon May  6 2002 ro@suse.de
- removed "-j3" from make call
* Fri May  3 2002 pthomas@suse.de
- Update to 0.6.1.
- Fix code to compile with gcc 3.1.
- Remove 'using namespace std;' from clanlib header.
- Add patch to support DESTDIR.
- Enable support for vorbis.
- Add freetype2, pkgconfig, DirectFB, libogg and libvorbis
  to #neededforbuild.
* Fri Apr 26 2002 stepan@suse.de
- fix lib path
* Thu Jan 31 2002 ro@suse.de
- changed neededforbuild <libpng> to <libpng-devel-packages>
* Wed Jan 23 2002 nadvornik@suse.cz
- updated to 0.5.3
* Thu Nov 22 2001 nadvornik@suse.cz
- fixed problem with absolute paths to resources
- do not use -mcpu=i686, it is not compiled correctly
* Tue Nov 13 2001 nadvornik@suse.cz
- fixed to compile on ia64
* Mon Nov 12 2001 nadvornik@suse.cz
- updated to 0.5.1
  - many bugfixes
  - updated documentation
* Mon Nov 12 2001 ro@suse.de
- no svgalib
* Thu Nov  8 2001 ro@suse.de
- use mesa-devel-packages in neededforbuild
* Thu Aug 23 2001 uli@suse.de
- build with RPM_OPT_FLAGS (i.e. with optimizations; seems to
  untrigger internal compiler error on IA64)
* Thu Jun 21 2001 nadvornik@suse.cz
- some fixes for 64bit archs
* Wed Jun  6 2001 nadvornik@suse.cz
- update to 0.5.0
* Tue May  8 2001 mfabian@suse.de
- bzip2 sources
* Thu Mar 22 2001 nadvornik@suse.cz
- freetype in neededforbuild was needless, removed
* Thu Mar 15 2001 ro@suse.de
- changed neededforbuild <mesaglu> to <xf86glu>
- changed neededforbuild <mesaglu-devel> to <xf86glu-devel>
* Wed Mar  7 2001 ro@suse.de
- changed neededforbuild <mesadev> to <mesa-devel>
* Mon Feb 26 2001 nadvornik@suse.cz
- fixed to compile on axp
* Mon Dec 11 2000 kukuk@suse.de
- Remove Requires, RPM can solve this better
* Fri Jul 28 2000 nadvornik@suse.cz
- compiled with xdevel3 to work with xf86 3.3.6
* Thu Jul 20 2000 nadvornik@suse.cz
- fixed bug with mouse in fullscreen
* Thu Jul 13 2000 nadvornik@suse.cz
- configure with --enable-vidmode
* Tue May 30 2000 nadvornik@suse.cz
- update to 0.4.4
* Mon May 22 2000 nadvornik@suse.cz
- used %%{_defaultdocdir}
- added mesadev to neededforbuild
* Fri Apr 28 2000 nadvornik@suse.cz
- fixed to compile with xf86-4.0
* Wed Apr 12 2000 nadvornik@suse.cz
- update to 0.4.3
- added BuildRoot
- added URL
* Thu Mar 16 2000 kukuk@suse.de
- Remove framebuffer support for SPARC
* Tue Mar 14 2000 ro@suse.de
- fixed to compile on alpha
* Mon Feb 28 2000 sndirsch@suse.de
- fixed some problems with undefined symbols in libclanMagick.so
- added shared library libMagick.so again for this
* Fri Feb 18 2000 sndirsch@suse.de
- Magicklib is now built statically and not longer included by
  clanlib
* Fri Feb 18 2000 sndirsch@suse.de
- updated to CVS tag "version-0-4-0-SuSE"
* Thu Feb 17 2000 sndirsch@suse.de
- updated to release 0.4.0
* Wed Feb  9 2000 sndirsch@suse.de
- changed group tag
* Thu Jan 20 2000 sndirsch@suse.de
- added Requires field for libpng
* Tue Dec 28 1999 sndirsch@suse.de
- created clanlib package

%_signature gpg
%_gpg_name Sibek
