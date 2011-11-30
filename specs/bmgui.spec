Name:           bmgui
Version:        0.1
Release:        0%{?dist} 
Summary:        Sibek Balance Machine GUI

Group:          Applications/System
License:        GPLv2+
URL:            http://www.sibek.ru
Source0:        %{name}-%{version}.tbz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildArch:      x86_64

Requires:       xinput_calibrator

%description
Sibek Balance Machine GUI for KonsulM

%prep
%setup -q -n %{name}

%build
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/fonts
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/i18n
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu
mkdir -p $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen
mkdir -p $RPM_BUILD_ROOT%{_sysconfdir}/init.d
mkdir -p $RPM_BUILD_ROOT%{_datadir}/pixmaps
mkdir -p $RPM_BUILD_ROOT%{_datadir}/applications

install -pm 755 bmgui $RPM_BUILD_ROOT%{_bindir}/
install -pm 755 files/bmgui_xinput_calibrator $RPM_BUILD_ROOT%{_bindir}/
install -pm 755 bmgui_start $RPM_BUILD_ROOT%{_bindir}/

install -pm 644 data/scripts/wizard.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/balance_progress.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/common.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/stats.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/start_screen.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/keyboard.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/main_menu.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/main_screen.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/disk_menu.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/layout_menu.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/message.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/scripts/oscilloscope.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/scripts/
install -pm 644 data/sprites/main_screen/texture1.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture10.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture8.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture9.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture7.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/sprites.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture2.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture3.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture11.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture4.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture0.jpg $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/wheel.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/keyboard.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/start_screen.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture6.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/disk_menu.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture0.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/layout_menu.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/resources.xml $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture5.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture12.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/misc.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/main_screen.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/texture1.jpg $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_screen/message.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_screen/
install -pm 644 data/sprites/main_menu/texture1.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/oscilloscope.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/stats.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture7.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/sprites.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture2.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture3.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture4.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture0.jpg $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/main_menu.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture6.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture0.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture8.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture9.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/wizard.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/resources.xml $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture5.png $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/icons.layers $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/sprites/main_menu/texture1.jpg $RPM_BUILD_ROOT%{_datadir}/%{name}/sprites/main_menu/
install -pm 644 data/fonts/LiberationSans-Bold.ttf $RPM_BUILD_ROOT%{_datadir}/%{name}/fonts/
install -pm 644 data/fonts/main_menu.xml $RPM_BUILD_ROOT%{_datadir}/%{name}/fonts/
install -pm 644 data/fonts/DS-DIGIB.TTF $RPM_BUILD_ROOT%{_datadir}/%{name}/fonts/
install -pm 644 data/fonts/main_screen.xml $RPM_BUILD_ROOT%{_datadir}/%{name}/fonts/
install -pm 644 data/sounds/ruler.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/stop_key.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/ruler_success.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/balance_success.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/key.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/sounds.xml $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/sounds/start_key.wav $RPM_BUILD_ROOT%{_datadir}/%{name}/sounds/
install -pm 644 data/i18n/en.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/i18n/
install -pm 644 data/i18n/ru.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/i18n/
install -pm 644 data/i18n/cn.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/i18n/
install -pm 644 data/main.lua $RPM_BUILD_ROOT%{_datadir}/%{name}/
install -pm 644 files/bmgui.png $RPM_BUILD_ROOT%{_datadir}/pixmaps/
install -pm 644 files/bmgui.desktop $RPM_BUILD_ROOT%{_datadir}/applications
install -pm 644 files/bminfo $RPM_BUILD_ROOT%{_sysconfdir}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%dir %{_bindir}
%{_bindir}/bmgui
%{_bindir}/bmgui_xinput_calibrator
%{_bindir}/bmgui_start

%defattr(-,root,root,-)
%dir %{_datadir}/%{name}
%{_datadir}/%{name}/scripts/wizard.lua
%{_datadir}/%{name}/scripts/balance_progress.lua
%{_datadir}/%{name}/scripts/common.lua
%{_datadir}/%{name}/scripts/stats.lua
%{_datadir}/%{name}/scripts/start_screen.lua
%{_datadir}/%{name}/scripts/keyboard.lua
%{_datadir}/%{name}/scripts/main_menu.lua
%{_datadir}/%{name}/scripts/main_screen.lua
%{_datadir}/%{name}/scripts/disk_menu.lua
%{_datadir}/%{name}/scripts/layout_menu.lua
%{_datadir}/%{name}/scripts/message.lua
%{_datadir}/%{name}/scripts/oscilloscope.lua
%{_datadir}/%{name}/sprites/main_screen/texture1.png
%{_datadir}/%{name}/sprites/main_screen/texture10.png
%{_datadir}/%{name}/sprites/main_screen/texture8.png
%{_datadir}/%{name}/sprites/main_screen/texture7.png
%{_datadir}/%{name}/sprites/main_screen/sprites.lua
%{_datadir}/%{name}/sprites/main_screen/texture2.png
%{_datadir}/%{name}/sprites/main_screen/texture3.png
%{_datadir}/%{name}/sprites/main_screen/texture9.png
%{_datadir}/%{name}/sprites/main_screen/texture11.png
%{_datadir}/%{name}/sprites/main_screen/texture4.png
%{_datadir}/%{name}/sprites/main_screen/texture0.jpg
%{_datadir}/%{name}/sprites/main_screen/wheel.layers
%{_datadir}/%{name}/sprites/main_screen/keyboard.layers
%{_datadir}/%{name}/sprites/main_screen/start_screen.layers
%{_datadir}/%{name}/sprites/main_screen/texture6.png
%{_datadir}/%{name}/sprites/main_screen/disk_menu.layers
%{_datadir}/%{name}/sprites/main_screen/texture0.png
%{_datadir}/%{name}/sprites/main_screen/layout_menu.layers
%{_datadir}/%{name}/sprites/main_screen/resources.xml
%{_datadir}/%{name}/sprites/main_screen/texture5.png
%{_datadir}/%{name}/sprites/main_screen/texture12.png
%{_datadir}/%{name}/sprites/main_screen/misc.layers
%{_datadir}/%{name}/sprites/main_screen/main_screen.layers
%{_datadir}/%{name}/sprites/main_screen/texture1.jpg
%{_datadir}/%{name}/sprites/main_screen/message.layers
%{_datadir}/%{name}/sprites/main_menu/texture1.png
%{_datadir}/%{name}/sprites/main_menu/oscilloscope.layers
%{_datadir}/%{name}/sprites/main_menu/stats.layers
%{_datadir}/%{name}/sprites/main_menu/texture7.png
%{_datadir}/%{name}/sprites/main_menu/sprites.lua
%{_datadir}/%{name}/sprites/main_menu/texture2.png
%{_datadir}/%{name}/sprites/main_menu/texture3.png
%{_datadir}/%{name}/sprites/main_menu/texture4.png
%{_datadir}/%{name}/sprites/main_menu/texture0.jpg
%{_datadir}/%{name}/sprites/main_menu/texture8.png
%{_datadir}/%{name}/sprites/main_menu/texture9.png
%{_datadir}/%{name}/sprites/main_menu/main_menu.layers
%{_datadir}/%{name}/sprites/main_menu/texture6.png
%{_datadir}/%{name}/sprites/main_menu/texture0.png
%{_datadir}/%{name}/sprites/main_menu/wizard.layers
%{_datadir}/%{name}/sprites/main_menu/resources.xml
%{_datadir}/%{name}/sprites/main_menu/texture5.png
%{_datadir}/%{name}/sprites/main_menu/icons.layers
%{_datadir}/%{name}/sprites/main_menu/texture1.jpg
%{_datadir}/%{name}/fonts/LiberationSans-Bold.ttf
%{_datadir}/%{name}/fonts/main_menu.xml
%{_datadir}/%{name}/fonts/DS-DIGIB.TTF
%{_datadir}/%{name}/fonts/main_screen.xml
%{_datadir}/%{name}/sounds/ruler.wav
%{_datadir}/%{name}/sounds/stop_key.wav
%{_datadir}/%{name}/sounds/ruler_success.wav
%{_datadir}/%{name}/sounds/balance_success.wav
%{_datadir}/%{name}/sounds/key.wav
%{_datadir}/%{name}/sounds/sounds.xml
%{_datadir}/%{name}/sounds/start_key.wav
%{_datadir}/%{name}/i18n/en.lua
%{_datadir}/%{name}/i18n/ru.lua
%{_datadir}/%{name}/i18n/cn.lua
%{_datadir}/%{name}/main.lua

%defattr(-,root,root,-)
%dir %{_datadir}/pixmaps
%{_datadir}/pixmaps/bmgui.png

%defattr(-,root,root,-)
%dir %{_datadir}/applications
%{_datadir}/applications/bmgui.desktop

%defattr(-,root,root,-)
%dir %{_sysconfdir}
%{_sysconfdir}/bminfo

%_signature gpg
%_gpg_name Sibek


