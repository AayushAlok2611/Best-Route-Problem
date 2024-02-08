Approach ->


Orders are assinged to delivery executives . These orders can have 3 states
1) RECEIVED -> Delivery executive has just received the order
2) PICKED_UP -> Delivery Executive has picked up the order
3) DELIVERED -> Delivery Executive has delivered the order

I have used Backtracking algorithm, to find the min time required to deliver all the orders assigned to the delivery executive.

I iterate through all the orders assigned to the executive and in one iteration I do only one thing for the order , i.e either 
the order is picked up or delivered , depending upon its state. Do nothing if the order has already been delivered.

Try all possible combinations of picking up the order from different restaurants , in different orders, and delivering them to different customers, in different orders, and return the minimum time , among all such combinations.


Assumptions ->
1) If we have 2 location , the function "getDistanceBetweenTwoLocations" will give us the distance between the 2 locations , the implementation details for this were not clear to me so I have left the function body blank.