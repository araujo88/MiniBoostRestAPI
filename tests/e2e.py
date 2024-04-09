import unittest
import requests

class TestPersonAPI(unittest.TestCase):
    BASE_URL = 'http://localhost:6969'

    def test_post_person(self):
        url = f"{self.BASE_URL}/v1/person"
        payload = {'name': 'John Doe', 'age': 30}
        headers = {'Content-Type': 'application/json'}

        response = requests.post(url, json=payload, headers=headers)
        self.assertEqual(response.status_code, 201)

    def test_get_persons(self):
        url = f"{self.BASE_URL}/v1/person"
        
        response = requests.get(url)
        self.assertEqual(response.status_code, 200)

    def test_get_unknown_route(self):
        url = f"{self.BASE_URL}/42"
        
        response = requests.get(url)
        self.assertEqual(response.status_code, 404)

    def test_get_person_by_id(self):
        url = f"{self.BASE_URL}/v1/person/0"
        
        response = requests.get(url)
        self.assertEqual(response.status_code, 200)

    def test_get_person_by_id_not_found(self):
        url = f"{self.BASE_URL}/v1/person/42"
        
        response = requests.get(url)
        self.assertEqual(response.status_code, 404)


if __name__ == '__main__':
    unittest.main()
