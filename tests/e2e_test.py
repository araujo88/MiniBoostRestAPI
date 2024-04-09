import pytest
import requests

BASE_URL = 'http://localhost:6969'

@pytest.mark.order(1)
def test_post_person():
    url = f"{BASE_URL}/v1/person"
    payload = {'name': 'John Doe', 'age': 30}
    headers = {'Content-Type': 'application/json'}
    response = requests.post(url, json=payload, headers=headers)
    assert response.status_code == 201

@pytest.mark.order(2)
def test_get_persons():
    url = f"{BASE_URL}/v1/person"
    response = requests.get(url)
    assert response.status_code == 200

@pytest.mark.order(3)
def test_get_person_by_id():
    url = f"{BASE_URL}/v1/person/0"
    response = requests.get(url)
    assert response.status_code == 200

@pytest.mark.order(4)
def test_get_person_by_id_not_found():
    url = f"{BASE_URL}/v1/person/42"
    response = requests.get(url)
    assert response.status_code == 404

@pytest.mark.order(5)
def test_delete_person_by_id():
    url = f"{BASE_URL}/v1/person/0"
    response = requests.delete(url)
    assert response.status_code == 204

@pytest.mark.order(6)
def test_not_found():
    url = f"{BASE_URL}/42"
    response = requests.get(url)
    assert response.status_code == 404
