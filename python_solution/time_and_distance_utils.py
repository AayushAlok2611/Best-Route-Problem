# Utility function to get distance between two locations
def getDistanceBetweenTwoLocations(location1, location2):
    # Logic to get the distance between 2 locations
    pass

# Utility function to get time to move between locations
def getTimeToMoveBetweenLocations(location1, location2, speed):
    distance = getDistanceBetweenTwoLocations(location1, location2)
    return distance / speed
