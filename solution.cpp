#include <vector>
#include <iostream>
#include <algorithm>  // Required for std::min and std::max
#include <climits> 
using namespace std;

//======= ENUMs ==========
enum ORDER_STATUS {RECEIVED,PICKED_UP,DELIVERED};

// ==================== Defining the data classes ===================
class Location{
    private:
    int latitude;
    int longitude;

    public:
    Location(){}
    Location(int lat,int longi){
        latitude = lat;
        longitude = longi;
    }
};

class Restaurant{
    private:
    Location location;

    public:
    Restaurant(Location loc)
    {
        location = loc;
    }
    Location getRestaurantLocation()
    {
        return location;
    }
};

class Customer{
    private:
    Location location;

    public:
    Customer(Location loc)
    {
        location = loc;
    }
    Location getCustomerLocation()
    {
        return location;
    }
};

class Order{
    private:
    Restaurant restaurant;
    Customer customer;
    double prepTime;
    ORDER_STATUS orderStatus;

    public:
    Order(Restaurant restaurant,Customer customer,int prepTime):restaurant(restaurant),customer(customer),prepTime(prepTime){
        orderStatus = RECEIVED;
    }

    Location getRestaurantLocation()
    {
        return restaurant.getRestaurantLocation();
    }

    Location getCustomerLocation()
    {
        return customer.getCustomerLocation();
    }
    double getPrepTime()
    {
        return prepTime;
    }
    bool isDelivered()
    {
        return orderStatus == DELIVERED;
    }
    bool isPickedUp()
    {
        return orderStatus == PICKED_UP;
    }
    bool isReceived()
    {
        return orderStatus == RECEIVED;
    }
    void setAsPickedUp()
    {
        orderStatus = PICKED_UP;
    }
    void setAsReceived()
    {
        orderStatus = RECEIVED;
    }
    void setAsDelivered()
    {
        orderStatus = DELIVERED;
    }
    ORDER_STATUS getStatus()
    {
        return orderStatus;
    }
};

class DeliveryExecutive{
    private:
    Location location;
    double speed;
    vector<Order> orders;

    public:
    DeliveryExecutive(){}
    Location getDeliveryExecutiveLocation()
    {
        return location;
    }
    double getSpeed()
    {
        return speed;
    }
    vector<Order> getOrderList()
    {
        return orders;
    }
    void setOrderList(vector<Order> orders)
    {
        this->orders = orders;
    }
    void setLocation(Location loc)
    {
        location = loc;
    }
    Location getLocation()
    {
        return location;
    }
    void setSpeed(double speed)
    {
        this->speed = speed;
    }
};

// =================== Util functions ===========================================

double getDistanceBetweenTwoLocations(Location location1,Location location2)
{
    // Logic to get the distance between 2 locations
}
double getTimeToMoveBetweenLocations(Location location1, Location location2, double speed)
{
    double distance = getDistanceBetweenTwoLocations(location1, location2);
    return distance/speed;
}


// ===================== Logic to get minimum time to deliver all the orders ================

/* 
Backtracking algorithm

We iterate through all the orders assigned to the executive and in one iteration we do only ont thing for the order either we 
pick up the order or we deliver the order.

Here we try all possible combinations of picking up the order from different restaurants and delivering them to different customers, and return
the minTime , among all such combinations

*/
double minTimeToDeliverAllOrders(DeliveryExecutive deliveryExecutive,double timeElapsed)
{
    bool allOrdersDelivered = true;
    vector<Order> orders = deliveryExecutive.getOrderList();
    double minTime = INT_MAX;
    for(Order order:orders)
    {
        if(order.isDelivered()) // no need to do anything 
        {
            continue;
        }
        else if(order.isReceived()) // need to pick up this order from restaurant
        {   
            allOrdersDelivered = false;

            Location currentDeliveryExecutiveLocation = deliveryExecutive.getDeliveryExecutiveLocation();
            Location restaurantLocation = order.getRestaurantLocation();
            double deliveryExecutiveSpeed = deliveryExecutive.getSpeed();
            
            double prepTimeForOrder = order.getPrepTime();
            double timeToTravelToRestaurant = getTimeToMoveBetweenLocations(currentDeliveryExecutiveLocation,restaurantLocation,deliveryExecutiveSpeed);
            double timeWhenExecutiveReachesRestaurant = timeElapsed + timeToTravelToRestaurant;
            double waitingTime = max((double)0, prepTimeForOrder - timeWhenExecutiveReachesRestaurant); 
            double timeTakenToPickUpOrder = timeToTravelToRestaurant + waitingTime;

            // mark order as picked up and move delivery executive to restaurant's location
            order.setAsPickedUp();
            deliveryExecutive.setLocation(restaurantLocation);
            deliveryExecutive.setOrderList(orders);

            double currentAnswer = timeTakenToPickUpOrder;
            currentAnswer += minTimeToDeliverAllOrders(deliveryExecutive, timeElapsed + timeTakenToPickUpOrder);

            // update the minTime
            minTime = min(minTime, currentAnswer);

            // backtrack
            order.setAsReceived();
            deliveryExecutive.setLocation(currentDeliveryExecutiveLocation);
            deliveryExecutive.setOrderList(orders);
        }
        else if(order.isPickedUp()) // need to deliver this order to the customer
        {
            allOrdersDelivered = false;

            Location currentDeliveryExecutiveLocation = deliveryExecutive.getDeliveryExecutiveLocation();
            Location customerLocation = order.getCustomerLocation();
            double deliveryExecutiveSpeed = deliveryExecutive.getSpeed();

            double timeToTravelToCustomer = getTimeToMoveBetweenLocations(currentDeliveryExecutiveLocation,customerLocation,deliveryExecutiveSpeed);
            double timeTakenToDeliverOrder = timeToTravelToCustomer;

            // mark order as delivered and move delivery executive to customer's location
            order.setAsDelivered();
            deliveryExecutive.setLocation(customerLocation);
            deliveryExecutive.setOrderList(orders);

            double currentAnswer = timeTakenToDeliverOrder;
            currentAnswer += minTimeToDeliverAllOrders(deliveryExecutive, timeElapsed + timeTakenToDeliverOrder);

             // update the minTime
            minTime = min(minTime, currentAnswer);

            // backtrack
            order.setAsPickedUp();
            deliveryExecutive.setLocation(currentDeliveryExecutiveLocation);
            deliveryExecutive.setOrderList(orders);
        }
    }
    if (allOrdersDelivered) return 0.0;
    return minTime;
}

int main()
{   
    DeliveryExecutive deliveryExecutive = DeliveryExecutive();
    Location startingLocation = Location(0,0);
    deliveryExecutive.setLocation(startingLocation);

    //code to populate the orders for the deliveryExecutive

    double requiredTime = minTimeToDeliverAllOrders(deliveryExecutive,0);

    return 0;
}