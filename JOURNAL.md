

# Trying my best to do cad

_Time spent: 5h_

Cad is so annoying because I know how to use fusion (just barely) and have no clue how to use onshape so I am stuck jumbing around between different softwares just to make a box. I made most of it in fusion but at then end of it my fusion started bugging and removed my progress randomly because my pcb was too difficult to render so I just had to use a online viewer and make sure they matched up. After this I just put it into tinkercad to add some text because I was too lazy to do it in fusion.
![fe](https://stasis.hackclub-assets.com/images/1782872452646-qfbv7q.png)

![image](https://stasis.hackclub-assets.com/images/1782872452646-qfbv7q.png)

# Grinded out all of the PCB

_Time spent: 3h_

Honestly the components were a lot bigger than i thought they would be making it harder to fit in all of my things but I generally found a good place for everything to go with the reset button being left of the antenna all the power stuff opposite of antenna and all of the sensor i2c stuff on the right of the antenna. I then compressed the power stuff as much as I could before I started routing. I started with the USB differential pair which took me around 5-6 tries but I was eventually able to place the 0 ohm resistors just right to get a good differential pair. From here it was pretty smooth sailing slight adjustments here and there obviously I kept my power traces thicker and routed out to the rest of the board. Once I got to the final electrode section it was honestly pretty tight but I was able to just 45 dgeree rotate the MRP121 giving it a nice routing into the pins of the mcu and the fpc connector. After this I just filleted the edges placed the ground planes stitching vias and adjusted the planes a bit to get some more area for vias then added silskcreen to finish of the electronics of this proejct
![Screenshot](https://stasis.hackclub-assets.com/images/1782871791566-bz2wd0.png)

![image](https://stasis.hackclub-assets.com/images/1782871791566-bz2wd0.png)

# Finished Schematic

_Time spent: 1h_

This part of the project was not that bad at all since all I had to do was read the esp32 documentation carefully and make sure I didnt accidentally use one of the strapping pins and other than that I just basically followed the datasheet. I did end up redoing where I decided to place I2C tho because I realized that based on the layout i planned earlier it would be easier to route this way instead. Lastly of course I routed the FPC and mrp121 which was thankfully pretty easy not too many passsives or anything because of its autoconfig.
![Screenshot ](https://stasis.hackclub-assets.com/images/1782869975473-84s2zx.png)

![image](https://stasis.hackclub-assets.com/images/1782869975473-84s2zx.png)

# Research(short) + Half the Schematic for second board

_Time spent: 2.5h_

Now I was thinking about this phase for a pretty long time tbh so I aleardy knew a lot on what I wanted to do but just did some short around 30 min research on the perfect FPC ZIF connector for this project which I eventually found. I also chose to use a 3.7V Lipo w USB-C charging via a usb pwr management ic and use 2 diodes to make sure the mcu i chose (esp32 s3 wroom) didn't get 2 power sources at once. The charging circuit was a little weird and I asked for some help w it and looked at some public schematics but I eventually got it I think.
![Screenshot](https://stasis.hackclub-assets.com/images/1782869888281-p91spa.png)

![image](https://stasis.hackclub-assets.com/images/1782869888281-p91spa.png)

# Routing the actual Foot

_Time spent: 7h_

To start off what I did was route out all of the traces in the fpc out to the main part pretty simple but I had to adjust some of my board outlines to avoid drc errors. From there I imported this image I found online that allowed me better recognize and draw the different zones I needed to measure and did my best to resize this to my pcb and use the polygon tool while this was on silkscreen(remember this) to get the rough shapes around it. 
![Screenshot ](https://stasis.hackclub-assets.com/images/1782868409940-9s9n51.png)
Okay so then I had all of the different regions zones out I had grounds that I would just via stitch later and my signals just flowed pretty effortlessly into each of the copper regions. I then constructed a way for me to reflect these onto the other half of the insole which I am pretty proud of. So what I did was place a temp via at the center of the rectangularish region that connected the 2 sides of the insole together and then what I would do is on the region itslef I would copy and paste the same region exactly on top and rotate the copy 180 on top of itself then I would reflect vertically ABOUT the temp via point  giving near perfect placements. After this I heard that since that top side would have the gnd regions as well as a general vgnd plane it is good practice to use vias around the regions to sort of isolate them and make it so their signals are the ones that matter which was tedious but pretty easy. 

Now lastly it was time to place the hateched ground planes but they were going everywhere all over the place like way beyond the board edges. I deteled some of the regions reset my editor renamed the ground net and did as much as I could to get this to work but always it never fixed itself. Then after so much frustration I realized that a super small amount of the board outline became silkscreen when I turned that other image earlier into silkscreen which wasted like literally an hour of my time tryign to figure that out. 

After that, I did some more research because I wasn't sure whether I should have a hatched region around my capactive pads and figured that it didn't provide any actual stability and it was just better to not use it as it could lead to the signal coupling with that ground rather than the region itself. At the end of this I just did some final adjustment work like deleting the random temportary stuff and rebuilding some of the planes to end of at this.
![Screenshot ](https://stasis.hackclub-assets.com/images/1782869426672-pjtdt5.png)

![image](https://stasis.hackclub-assets.com/images/1782868409940-9s9n51.png)
![image](https://stasis.hackclub-assets.com/images/1782869426672-pjtdt5.png)

# Schematic (but not really) and Outline of the board

_Time spent: 3h_

I first started out with the schematic which was very fast as all I really had to do was descide on what 6 major foot zones I wanted to track.
![Screenshot ](https://stasis.hackclub-assets.com/images/1782867772285-9wkbzm.png)
After this I went to my physical shoe and took out the shoesole took a photo and adjusted with the outlining of it so that the only part that is outlined is the actual borders itself. After this I then exported that as a DXF reimported it into Easyeda and had to relearn some of the alignment reflection rotation stuff that I learned a while back from a youtube video to duplicate the other half of the shoe insole onto the other side and line them up just right. After this I had to connect those 2 halves together which involved cutting up that original dxf into a dxf without that hole reduplicating + aligning it and drawing a board line to connect the 2 halves togther. I also saved some time by making sure to make a hole for the ribbon calble to go out as well. Lastly, I read that it was bad to have 90 degree beends and to instead have curved bends so I went back in deleted some lines and used the 3 point polyarc tool to make the board outline.
![Screenshot ](https://stasis.hackclub-assets.com/images/1782868076016-w1vc9q.png)

![image](https://stasis.hackclub-assets.com/images/1782867772285-9wkbzm.png)
![image](https://stasis.hackclub-assets.com/images/1782868076016-w1vc9q.png)

# Lots of random second guessing

_Time spent: 3h_

I made a pretty important descision that it is not safe to have a Lipo Battery near my foot and I would have to make an external PCB to fold up and out the ankle region to connect to the pcb. For this I had 2 options that I came up with JST connectors and a FPC ribbon cable. The ribbon cable is much cheaper and easier to manufacture but higherchance I mess up but the JST connector is more expensive harder to source everything but high chance it works. I spent 30 mins here and 30 mins there doing research for either one before finally deciding to settle on the ribbon cable primarily for cost. I then also had another dilema as in my research I heard about approaching this with FSRs( Force sensitive resistors) which simplifies a lot of the process and I think could also help increase the likeliehood this works. I actually did a lot of research on how to integreate fsrs but thankfully I found out that JLCPCB maxes out at around 10kg of force so there was no way that was an option anymore.
![Screenshot](https://stasis.hackclub-assets.com/images/1782867660800-7mpwy9.png)

just ended up reusing this for easyeda lol

![image](https://stasis.hackclub-assets.com/images/1782867660800-7mpwy9.png)

# Research init

_Time spent: 4h_

So if you have seen my most recent project my capacitive touch sesnor based rubiks cube you will know that I wish that I used a continous capacitive sensor rather than the binary (on/off sensor) that I was using. So while I was thinking about what cool applications for a MRP121 that I could use were and since I have been playing a lot of basketaball recently I remembered watching https://www.youtube.com/watch?v=yaZKmCq6sRQ a while back and chose to use the context of capacitance for this PCB. The idea is there is a flex pcb with a esp32 that relays the infoform the mrp121 and I can (hopefully) fit all of the elctronics into the midfoot(the part that is usually arched) so it doesnt actually break but is wearable. For more information on the actual capacitive sensor I read Practical electronics for inventors and their chapter on conductivity and dielectric constants and a whole lot of other stuff I tried my best to understand lol
![Screenshot](https://stasis.hackclub-assets.com/images/1782866935879-2w8edv.png)

![image](https://stasis.hackclub-assets.com/images/1782866935879-2w8edv.png)
