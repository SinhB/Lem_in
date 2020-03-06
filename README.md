# Lem_in

The main goal of this project is to find the most optimal way for X number of ants to traverse an ant farm, from a start room into and sink room.<br/>
All the ants have to reach the sink room with the minimum steps possible.

<h1>Ant farm specifications :</h1><br/>
- Tubes and rooms<br/>
- A starting room define by ##start<br/>
- A sink room define by ##end<br/>
- A tube joins two rooms to each other<br/>
- A room can be linked to an infinite number of rooms and by as many tubes as deemed necessary<br/>
- A room can only contain 1 ant at a time<br/>
<br/>

Example of ant farm code and his representation:<br/>

![Screen Shot 2020-02-27 at 11 12 52 AM](https://user-images.githubusercontent.com/24353380/75434812-65e63f00-5952-11ea-8b26-b9493124cddb.png)
![Screen Shot 2020-02-27 at 11 13 51 AM](https://user-images.githubusercontent.com/24353380/75435165-eefd7600-5952-11ea-8cc1-89c4cd4ed931.png)
<br/><br/>

<h1>Algorithm :</h1><br/>

I used an inspired version of Edmond Karp algorithm, with mutiple BFS (Breadth-first search) to find shortests paths in this ant farm graph structure.<br/>
Parameters are :<br/>
- The number of ants<br/>
- The ant farm (including the rooms and the tubes)<br/>

<h1>Installation :</h1><br/>

<pre><code>git clone https://github.com/SinhB/Lem_in.git & cd Lem_in & make</code></pre><br/>

<h1>Usage :</h1><br/>

- <pre><code>./lemin < antfarm.file</code></pre><br/>
- you can use <code>-s</code> and <code>-c</code> option, <code>-s</code> print the number of steps, <code>-c</code> add colors for better visualization<br/>

<h1>Example :</h1><br/>

![Screen Shot 2020-02-27 at 11 49 11 AM](https://user-images.githubusercontent.com/24353380/75437882-3dad0f00-5957-11ea-8a30-64a116b3bd65.png)
