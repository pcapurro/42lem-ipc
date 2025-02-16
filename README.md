# 42lem-ipc
### « Processes fighting for their life »

Players are processes joining the game, represented by their team number.
<br/>
The first player launching the game will be the host and will print the game.
<br/>

Players from the same team will communicate to choose a target.
<br/>
If a player is surrounded by at least 2 players of the same team, he dies and leaves the game.
<br/>
The last team alive on the board wins the game.
<br/>

```
./42lem-ipc [team number]
```
Help feature `-h` (or `--help`) is supported.
<br/>
