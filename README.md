**Approach ->**

Orders are assinged to delivery executives . These orders can have 3 states
1) RECEIVED -> Delivery executive has just received the order
2) PICKED_UP -> Delivery Executive has picked up the order
3) DELIVERED -> Delivery Executive has delivered the order

I have used Backtracking algorithm, to find the min time required to deliver all the orders assigned to the delivery executive.

I iterate through all the orders assigned to the executive and in one iteration I do only one thing for the order , i.e either 
the order is picked up or delivered , depending upon its state. Do nothing if the order has already been delivered.

Try all possible combinations of picking up the order from different restaurants , in different orders, and delivering them to different customers, in different orders, and return the minimum time , among all such combinations.

**Time And Space complexity Analysis ->**

The time complexity of the provided recursive function minTimeToDeliverAllOrders can be analyzed in terms of the number of recursive calls and the work done in each call.

Let n be the number of orders that the DeliveryExecutive has in its order list.

The function explores all possible combinations of picking up and delivering orders. In the worst case, each order can be in one of three states: received, picked up, or delivered.

For each order, the function makes recursive calls for each state, leading to an exponential number of recursive calls.

Let's analyze the time complexity:

For each order, the function makes three recursive calls (one for each state: received, picked up, and delivered).
The function does a constant amount of work for each order, including calculations based on the locations and speeds.
The recursion depth is at most n because the function explores the state space for each order.
Therefore, the overall time complexity is exponential in terms of the number of orders: *O(3^n)*

The space complexity is the depth of the recursion stack -> *O(n)*


**Assumptions ->**

1) If we have 2 location , the function "getDistanceBetweenTwoLocations" will give us the distance between the 2 locations , the implementation details for this were not clear to me so I have left the function body blank. I have assumed that the time complexity for this operation is constant.