# QT Ham Audio Rec 

This program was developed using QT 6.3 on a Mac Silicon M1, it has not been extensivly tested on 
other hardware platforms.

## Why do you need this ? 

If you have a modern up-to-date contest logger (WinLog, N1NM[?] or WriteLog) then firstly well done, but 
as you are running on windows - I suspect that there are lots of other options also available to you.

I decided some months ago, to write my own contest logger. Which I have now sucessfully done, and one of 
things that I forgot to do was to provide a mechanism to record the contest audio.

You may with to read [https://cqww.com/blog/new-recording-rule/](https://cqww.com/blog/new-recording-rule/)

Specifically 

```text
XII.C. Audio Recordings: Any single operator entrant (see V.A.1) competing for a 
top three finish at the (a) World, (b) Continent , or (c) USA levels, must record 
the transmitted and received audio as heard by the operator for the duration of 
the contest operation.

The recording must be in a common format (e.g., mp3) and should include the audio 
to each ear as a separate channel.
"
```
A further clarification is provided for 2021 [https://cqww.com/blog/2021-cqww-rules-updates/](https://cqww.com/blog/2021-cqww-rules-updates/)

```text
As a reminder, audio recordings may be requested for your entry as part of the log 
checking process. Any single operator entrant competing for a top-five finish at the
(a) World, (b) Continent, or (c) USA levels, including Classic Overlay, must record
the transmitted and received audio as heard by the operator for the duration of 
the contest operation. Failure to respond to this request may result in your log 
being reclassified or disqualified.
```

You have been warned....


## Why Record the Contest Audio ?

I am sure there are many reasons why .. but here are a couple

  - to verify that you really did hear using your own radio (and not say a remote SDR !)
  - to verify that those 'Unique' calls are really unique... and not a figment of your imagination or fat-fingers.
  ****
## How much data does this store ?

If you store in a WAV format (which I **MOST** strongly suggest that you **NO NOT**), you will need 15Gb/Day (table below)

However - and remember I am using a Mac (so your Windows mileage may vary here), using FLAC and storing as a file 
type of m4a (this is Apple's version of MP3). My data storage is as follows 

MP3 Format on mac generated using setMediaFormat(QMediaFormat::MP3);


| Format | 1 Minute | 1 Hour | 1 Day |
|--------|----------|--------|-------|
| WAV    |  10   Mb | 600 Mb | 14.4Gb|
| FLAC   |   0.9 Mb |  54 Mb |  1.3Gb| 
| MP3    |   0.9 Mb |  54 Mb |  1.3Gb| 

## What Length of Recording should you make ?

Well as long as it covers the entire contest period that you operate for I think you would be OK... however, it may make contest direction's task of verifying what you were doing a little more difficult.

But if the recordings were 1 hour in length - and they started EXACTLY at the contest start time - this would not be too bad for them.

## Could I join my Morning and Afternoon Recordings ?

If (like me) you tend to operate from 0600-1200 and then from 1400-2000 I would have the following files (Contest is IOTA)

  - IOTA_2022-07-12_00_23_00_291.m4a
  - IOTA_2022-07-13_00_00_00_291.m4a
  - IOTA_2022-07-13_00_01_00_293.m4a
  - IOTA_2022-07-13_00_02_00_285.m4a
  - IOTA_2022-07-13_00_03_00_296.m4a
  - IOTA_2022-07-13_00_04_00_281.m4a
  - IOTA_2022-07-13_00_07_15_281.m4a
  - IOTA_2022-07-13_00_08_15_231.m4a

etc

You can see I only started the Afternoon session at 14:15 (local) 07:15z.

You can join these files together using SOX... 

	sox -i IOTA_2022-07-12_00_23_00_291.m4a,IOTA_2022-07-13_00_00_00_291.m4a,IOTA_2022-07-13_00_01_00_293.m4a,IOTA_2022-07-13_00_02_00_285.m4a -o IOTA_AM_23_00-04_00.m4a 
	
Always create a new file - becuase you are required to keep the original files !!!



