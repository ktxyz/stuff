# Foliage Farming Prototype
Overview and explanation of Foliage Farming.

## Foliage Manipulation
We store foliage instances as simple **[[FoliageInstancedMeshComponent]]** instances. Player can add a new instance by clicking **LMB** on the surface. He can also remove an instance by clicking **RMB** while looking at it.

New instance gets added to the closest available **[[FoliageInstacedActor]]** (which are all pre-spawned so that they are taken into account by **[[WorldPartition]]**). To spawn them we only need a new location to add a new instance. And to remove them we need ID of their instance (which is given as Hit Item from **[[LineTrace]]**).
### Problems
While this approach is simple seems rather efficient it has a rather large problem. We are not able to directly change material of this instance. Which means that in order to do some highlighting or selection we would need to use some sort of tricks (I was thinking about a outline inside material itself branched behind **[[Material Parameter Collection]]** with currently traced Hit Item - although I'm not sure if material can access instanced ID). I didn't attempt solving this problem in my prototype.
## Save System
Save system I've written is kind of decentralized. **SaveManager** actor (although since it's singular maybe it should be rewritten as **[[Subsystem]]**?) serves only for 3 things (maybe 4 if we need **Load Last Save** functionality as we also need caching last save):
1. Load Save from Slot
2. Inform all Actors save is loaded
3. Save Data to Slot
4. (Optional) Keep cached save
Step 4 is required because the Actors update save game object between manual saves.

**[[FoliageInstacedActor]]** could be extended in C++ to implement Save/Restore behavior. Instead I opted for proxy actors - that way whole project could be easily done using **[[Blueprints]]** only! There is a large optimization which could be added to the project - caching state of instances of foliage instead of removing all and re-adding saved ones. 
### Restore/Save
**SaveManager** simply loads data, sets flag that it had loaded the data and calls dispatcher for anyone interested. Actors in this structure are self-responsible for restoring and saving own state. This structure allows saving and restoring state of actors that are part of **[[WorldPartition]]** system.
#### Begin Play
When actor comes to life it binds to **SaveManager**'s dispatcher and checks if the data is already loaded - if it is it restores itself immediately. This way even actors that are unloaded on start of the game will correctly restore their state when streamed-in.
#### End Play
When actor is unloaded (by streaming) it saves its data inside **SaveManager**. This ensures that if we create a new instance in some cell, which then will be unloaded before we save the game the instance's save data is still correctly handled.
### Caching
For **Load Last Save** functionality we need to keep 2 save objects in SaveManager:
1. Current with new data from unloaded cells
2. Last cached one from actual save moment

