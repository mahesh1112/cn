def is_valid_IPv4(ip):
    segments = ip.split('.')
    if len(segments) != 4:
        return False

    for segment in segments:
        if not segment.isdigit():
            return False
        if not (0 <= int(segment) <= 255):
            return False

    return True

def calculate_network_host_addresses(ip, mask):
    ip_components = [int(x) for x in ip.split('.')]
    mask_components = [int(x) for x in mask.split('.')]

    network_address = [ip_components[i] & mask_components[i] for i in range(4)]
    host_address = [ip_components[i] & ~mask_components[i] for i in range(4)]

    return '.'.join(map(str, network_address)), '.'.join(map(str, host_address))

print("SUBNETTING AND SUBNET MASK")
IP = input("Enter IP Address: ")
if is_valid_IPv4(IP):
    IP_components = IP.split('.')
    class_check = int(IP_components[0])
    mask = ""
    if class_check > 0:
        if class_check <= 127:
            mask = "255.0.0.0"
            print("Class A IP Address")
            print("SUBNET MASK: ", mask)
        elif 128 <= class_check <= 191:
            mask = "255.255.0.0"
            print("Class B IP Address")
            print("SUBNET MASK: ", mask)
        elif 192 <= class_check <= 223:
            mask = "255.255.255.0"
            print("Class C IP Address")
            print("SUBNET MASK: ", mask)
        elif 224 <= class_check <= 239:
            #mask = "255.0.0.0"
            print("Class D IP Address")
            #print("SUBNET MASK: ", mask)
        elif 240 <= class_check <= 254:
            #mask = "255.0.0.0"
            print("Class E IP Address")
            #print("SUBNET MASK: ", mask)

        if(class_check >= 224):
            network_address, host_address = calculate_network_host_addresses(IP, mask)
            print("NETWORK ADDRESS:", network_address)
            print("HOST ADDRESS:", host_address)
        else:
            print("This class has no subnet mask")

else:
    print("Invalid IP Address")
