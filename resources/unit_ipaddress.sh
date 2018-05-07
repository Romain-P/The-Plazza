echo -e "Test plain text"
echo -e "test_ipaddress IP_ADDRESS" | ../plazza 1 --debug
echo -e "\nTest ciphered text"
echo -e "test_ciphered_ip IP_ADDRESS" | ../plazza 1 --debug