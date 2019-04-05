# Scheme

* Timer
* Viewer
* Merger button
* Shelf button
* Shelf dock
* Merger dock
* Merger
* Shelf
* Card

1.	If a card on Shelf Dock is hovered, Viewer shows up and Merger Dock hides. Viewer gets the card from Shelf and displays the card’s info.
2.	If a card on Shelf Dock is clicked, Viewer hides and Merger Dock shows. Merger Dock checks if there is space and tells the card the destination. The card moves to the destination. Shelf Dock hides the card.
3.	If a card on Merger Dock is clicked, Merger Dock clears up the space. Shelf Dock unhides the card. Merger Dock hides the card.
4.	If Merger Dock can merge, Merger Button unhides.
5.	If Merger Button is clicked, it calls Merger to merge. Merger takes the two cards from Shelf and merge.
6.	If the merging succeeded, Merger will generate a new card and add it to Shelf. Merger Dock and Shelf Dock will hide the two cards
7.	If the merging failed, Merger will tell Merger Dock to hide and the two cards and Merger will tell Shelf Dock to unhide and the two cards.
8.	If Shelf has more than 4 cards, Shelf Button unhides.
9.	If Shelf Button is clicked, Shelf Button will ask Shelf Dock to display first 4 cards or last 4 cards, depending on the original state.
10.	Timer countdowns.
11.	If Timer ends, Timer tells game window that window state is failure.
12.	If Shelf unhides the last card, Shelf tells game window that window state is victory.
