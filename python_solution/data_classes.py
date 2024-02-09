from constants import ORDER_STATUS

# Class definition for Location
class Location:
    def __init__(self, lat, longi):
        self.latitude = lat
        self.longitude = longi

# Class definition for Restaurant
class Restaurant:
    def __init__(self, loc):
        self.location = loc

    def getRestaurantLocation(self):
        return self.location

# Class definition for Customer
class Customer:
    def __init__(self, loc):
        self.location = loc

    def getCustomerLocation(self):
        return self.location

# Class definition for Order
class Order:
    def __init__(self, restaurant, customer, prepTime):
        self.restaurant = restaurant
        self.customer = customer
        self.prepTime = prepTime
        self.orderStatus = ORDER_STATUS.RECEIVED

    def getRestaurantLocation(self):
        return self.restaurant.getRestaurantLocation()

    def getCustomerLocation(self):
        return self.customer.getCustomerLocation()

    def getPrepTime(self):
        return self.prepTime

    def isDelivered(self):
        return self.orderStatus == ORDER_STATUS.DELIVERED

    def isPickedUp(self):
        return self.orderStatus == ORDER_STATUS.PICKED_UP

    def isReceived(self):
        return self.orderStatus == ORDER_STATUS.RECEIVED

    def setAsPickedUp(self):
        self.orderStatus = ORDER_STATUS.PICKED_UP

    def setAsReceived(self):
        self.orderStatus = ORDER_STATUS.RECEIVED

    def setAsDelivered(self):
        self.orderStatus = ORDER_STATUS.DELIVERED

    def getStatus(self):
        return self.orderStatus

# Class definition for DeliveryExecutive
class DeliveryExecutive:
    def __init__(self):
        self.location = Location(0, 0)
        self.speed = 0.0
        self.orders = []

    def getDeliveryExecutiveLocation(self):
        return self.location

    def getSpeed(self):
        return self.speed

    def getOrderList(self):
        return self.orders

    def setOrderList(self, orders):
        self.orders = orders

    def setLocation(self, loc):
        self.location = loc

    def getLocation(self):
        return self.location

    def setSpeed(self, speed):
        self.speed = speed
