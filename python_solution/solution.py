from typing import List
from data_classes import DeliveryExecutive, Location
from time_and_distance_utils import getTimeToMoveBetweenLocations

# Main logic to get minimum time to deliver all orders
def minTimeToDeliverAllOrders(deliveryExecutive, timeElapsed):
    allOrdersDelivered = True
    orders = deliveryExecutive.getOrderList()
    minTime = float('inf')

    for order in orders:
        if order.isDelivered():
            continue
        elif order.isReceived():
            allOrdersDelivered = False

            currentDeliveryExecutiveLocation = deliveryExecutive.getDeliveryExecutiveLocation()
            restaurantLocation = order.getRestaurantLocation()
            deliveryExecutiveSpeed = deliveryExecutive.getSpeed()

            prepTimeForOrder = order.getPrepTime()
            timeToTravelToRestaurant = getTimeToMoveBetweenLocations(currentDeliveryExecutiveLocation,
                                                                     restaurantLocation,
                                                                     deliveryExecutiveSpeed)
            timeWhenExecutiveReachesRestaurant = timeElapsed + timeToTravelToRestaurant
            waitingTime = max(0.0, prepTimeForOrder - timeWhenExecutiveReachesRestaurant)
            timeTakenToPickUpOrder = timeToTravelToRestaurant + waitingTime

            order.setAsPickedUp()
            deliveryExecutive.setLocation(restaurantLocation)
            deliveryExecutive.setOrderList(orders)

            currentAnswer = timeTakenToPickUpOrder
            currentAnswer += minTimeToDeliverAllOrders(deliveryExecutive, timeElapsed + timeTakenToPickUpOrder)

            minTime = min(minTime, currentAnswer)

            order.setAsReceived()
            deliveryExecutive.setLocation(currentDeliveryExecutiveLocation)
            deliveryExecutive.setOrderList(orders)
        elif order.isPickedUp():
            allOrdersDelivered = False

            currentDeliveryExecutiveLocation = deliveryExecutive.getDeliveryExecutiveLocation()
            customerLocation = order.getCustomerLocation()
            deliveryExecutiveSpeed = deliveryExecutive.getSpeed()

            timeToTravelToCustomer = getTimeToMoveBetweenLocations(currentDeliveryExecutiveLocation,
                                                                   customerLocation,
                                                                   deliveryExecutiveSpeed)
            timeTakenToDeliverOrder = timeToTravelToCustomer

            order.setAsDelivered()
            deliveryExecutive.setLocation(customerLocation)
            deliveryExecutive.setOrderList(orders)

            currentAnswer = timeTakenToDeliverOrder
            currentAnswer += minTimeToDeliverAllOrders(deliveryExecutive, timeElapsed + timeTakenToDeliverOrder)

            minTime = min(minTime, currentAnswer)

            order.setAsPickedUp()
            deliveryExecutive.setLocation(currentDeliveryExecutiveLocation)
            deliveryExecutive.setOrderList(orders)

    if allOrdersDelivered:
        return 0.0

    return minTime

# Main function
def main():
    deliveryExecutive = DeliveryExecutive()
    startingLocation = Location(0, 0)
    deliveryExecutive.setLocation(startingLocation)

    # Code to populate the orders for the deliveryExecutive

    requiredTime = minTimeToDeliverAllOrders(deliveryExecutive, 0)

if __name__ == "__main__":
    main()