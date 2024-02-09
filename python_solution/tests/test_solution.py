import unittest
from unittest.mock import Mock
from python_solution.data_classes import DeliveryExecutive, Location, Order
from python_solution.solution import minTimeToDeliverAllOrders

class TestDeliverySystem(unittest.TestCase):

    def test_all_orders_delivered(self):
        delivery_executive = DeliveryExecutive()
        location = Location(0, 0)
        delivery_executive.setLocation(location)

        # Create mock order with status DELIVERED
        mock_order = Mock(spec=Order)
        mock_order.isDelivered.return_value = True

        # Set up the order list for the delivery executive
        delivery_executive.setOrderList([mock_order])

        result = minTimeToDeliverAllOrders(delivery_executive, 0)

        # Assert that when all orders are already delivered, the result is 0.0
        self.assertEqual(result, 0.0)

if __name__ == '__main__':
    unittest.main()