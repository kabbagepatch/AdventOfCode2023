A relatively easy problem, I decided to do the first part in a manual way, despite suspecting it won't work in part two. I counted all the empty rows and columns, and made a new universe and then counted all the Manhattan distances to get the sum of all the distances.

For part two, of course we needed to expand it a million times. But the solution was still easy enough. Instead of manually expanding the universe and making a new 2d array, I just checked how many empty rows and column I cross during the Manhattan distance calculation, and added a million instead of one for that row/column.
