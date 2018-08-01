
Debian
====================
This directory contains files used to package Jadepayd/Jadepay-qt
for Debian-based Linux systems. If you compile Jadepayd/Jadepay-qt yourself, there are some useful files here.

## Jadepay: URI support ##


Jadepay-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Jadepay-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Jadepayqt binary to `/usr/bin`
and the `../../share/pixmaps/Jadepay128.png` to `/usr/share/pixmaps`

Jadepay-qt.protocol (KDE)

