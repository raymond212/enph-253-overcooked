from picamera2 import Picamera2, Preview
import cv2 as cv

def mark_bun(image):
    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    _, thresh = cv.threshold(gray, 50, 255, cv.THRESH_BINARY)
    contours, _ = cv.findContours(thresh, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    largest_contour = max(contours, key=cv.contourArea)
    output = image.copy()
    cv.drawContours(output, [largest_contour], -1, (0,0,255), 3)
    M = cv.moments(largest_contour)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    cv.circle(output, (cX,cY), 25, (0,0,255), -1)
    return output


def main():
    picam = Picamera2()
    camera_config = picam.create_still_configuration(
        main={"size": picam.sensor_resolution},
    )
    picam.configure(camera_config)
    picam.start()

    while True:
        frame = cv.cvtColor(picam.capture_array(), cv.COLOR_RGB2BGR)
        output = mark_bun(frame)
        cv.imshow('Img', output)
        if cv.waitKey(20) & 0xFF == ord('q'):
            break

    picam.stop()
    cv.destroyAllWindows()


if __name__ == '__main__':
    main()