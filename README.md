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

