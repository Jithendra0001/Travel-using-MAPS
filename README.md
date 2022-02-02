# Travel_with_MAPS  
## This Project is under Development
## Theme  
* You are a tourist. You want to go from one place to another place.  
* So, You bought a map of cities. _You saw that every city has a bus station but only Some cities have railway station._  
* You asked me to plan your journey.  

This project is under development

## Key points
1) By default,  
(i) Bus takes 3 Units of time from one place to adjacent place.  
(ii) Train takes 2 Units of time from one place to adjacent place.  

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
