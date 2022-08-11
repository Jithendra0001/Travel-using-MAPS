# Travel_with_MAPS 

* An algorithm for finding the path that takes **minimum time** to travel from one
city to another city in a map of cities where some cities have railway
stations and some cities have bus stations 

## Key points  
* It is assumed that, in a given period, the distance travelled by the train is twice that travelled by the bus.
* C++ Language is used in this project.
* Graph data structure is used.


## Example  
### CityMap:  
1) Here is a sample map of 13 cities with City1, city8 and city13 have railway stations.  
 ```
             city4               city8(T)
              /                    /
 City1(T)--city3--city5--city6--city7--city9--city10
     \             /       \                   /
       --------city2      City11--------------city12---city13(T)
                 
 ```  
#### Input:  
    From address: City1
    To address: City12
#### Output:
    City1--(Train)-->City13--(Bus)-->City12
#### Explanation:
    1) The train and bus depart at City1.
    2) When the train is at city11, the bus is at city5
    3) When the train is at city13, the bus is at city6
    4) Then the passenger goes from city13 to city12 by bus
