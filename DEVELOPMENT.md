* 4.18 Made initial project with ofxCV and ofxGUI
* 4.19 Added a button to make a default (hard coded) image gray
* 4.23 Changed the grayscale button to a toggle, added another toggle to show faces, added a button to clear filters
* 4.24 Attempted to implement selecting a portion of the picture but didn't work, implemented selecting a picture from file explorer
* 4.25 Tried to figure out how to let the user input a link for a picture, but the text box dialogue didn't allow for long enough string
* 4.27-28 Added capability to turn on video, still working on tracking the face - the coordinate system is messed up so the box isn't around the correct spot
* 4.30 Box follows face properly
* 5.2
    * Add ability to turn on/off grayscale/face detection on video
    * Add ability to take and save picture
    * Add ability to toggle blurred faces
    * Add snapchat-like face tracking filters (was a lot of struggling on how to not rescale the image every time, but not recopy it since it'll slow down video)
    * Did some fancy matrix stuff with face tracking filters, struggled with understanding how to do that
    * Add top hat, Harry Potter, and Game of Thrones face tracking filters
    * Edit code for quality and readability
