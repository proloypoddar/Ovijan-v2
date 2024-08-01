import cv2

# Replace with your Raspberry Pi's IP address
stream_url = "http://192.168.0.105:8080/?action=stream"

# Open the video stream
cap = cv2.VideoCapture(stream_url)

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break
    
    # Display the frame
    cv2.imshow("Frame", frame)

    # Exit on pressing 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and close the windows
cap.release()
cv2.destroyAllWindows()
