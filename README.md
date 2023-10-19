# Linked data map

*All the code examples in the readme is pseudocode. It's not possible to use it in real code.*

### ***How it works:***

We have a map (dictionary) that contains pairs of template types and set pointers (*clasters*). Example:
```py
map = {
    "a": set <T>,
    "b": set <T>,
    "c": set <T>
}
```

### ***Functions:***

* Add link (A to B). There are three different cases.
    - **A and B are not in the map** yet. In this case we have to add them both to the map, in the same time creating a new *claster*.  

        **Complexity: O(log(N))**  
        
        ```py
        map.add (A, B) # add new data points

        map [A] = set <T> # new claster
        map [B] = map [A]              # same claster

        map [A].add (A, B) # appending A and B to the claster
        ```
    - **A or B (only one) is in the map.** In the case we have to insert a new element into a *claster*. In the example B is appended to A *claster*.  

        **Complexity: O(log(N))**

        ```py
        map.add (B) # add a new data point

        map [B] = map [A] # set the claster

        map [A].add (B) # append to the claster
        ```

    - **A and B are in the map.** In this case we have to merge these two *clasters* together into one. To decrease memory consuming we won't create a new *claster*, but will move the data points from the smaller *claster* to bigger.  

        **Complexity: O(N)** *where N is the size of smaller claster*  

        ```py
        smaller claster = smaller of (map [A], map [B])
        bigger claster = bigger of (map [A], map [B])

        bigger claster.add (smaller claster)

        for each data point in smaller claster do:
            map [data point] = bigger claster

        delete smaller claster
        ```

* Remove data point (A). So called remove link. There are two cases.
    - **A is in the claster with more than 2 elements.** In this case we just remove an element from map and *claster*.  

        **Complexity: O(log(N))**  

        ```py
        claster = map [A]
        map.remove (A)
        claster.remove (A)
        ```

    - **A is in the claster with only 2 elements.** In the case we have to remove the entire claster to save the data stability.  

        **Complexity: O(log(N))**  

        ```py
        claster = map [A]

        for each data point in claster do:
            map.remove (data point)

        delete claster
        ```

* **Count linked (A).** Returns unsigned integer number.  

    **Complexity: O(1)**  

* **Are linked (A and B)** If they are in the same *claster*, then returns *True*. Otherwise returns *False*.  

    **Complexity: O(1)**