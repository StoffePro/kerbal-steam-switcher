# kerbal-steam-switcher
When Kerbal 1.4 came around, and several of my favourite mods
announced they weren't going to update to 1.4, I got really annoyed
that steam would only track playtime etc for the one specific version
you've configured through steam, because I'm kinda anal.

So I wrote this little tool to spoof steam into tracking all your
installs.

I know it sucks -- I know the code is butt-pug-fugly-ugly-ugly, but I
fucking hate c++, so I'm not going to spend any more time on  this
than I absolutely need to. 


# dependencies
kerbal-steam-switcher.exe reads installation dirs from CKAN,
so you need to have all your installs belong to CKAN. 


# installation
- Copy kerbal-steam-switcher.exe to a folder of your choosing 
- In your steam library
    - right click Kerbal
    - Set Launch Options
    - "C:\path\to\kerbal-steam-switcher.exe" %command%

# Copyright
Copyright 2018 Gunnar Horrigmo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Project website and source: https://github.com/StoffePro/kerbal-steam-switcher