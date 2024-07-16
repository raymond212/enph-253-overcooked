#include <navigator.h>

namespace Navigator {
  double position;
  YPosition yPosition;
  FacingDirection facingDirection;

  void setupNavigator() {
    position = 2.25;
    yPosition = YPosition::TAPE;
    facingDirection = FacingDirection::RIGHT;
  }

  void navigateToStation(Station station) {
    if (ROBOT_ID == 0 && station.table == Table::BOTTOM) {
      // Bottom table is not for top robot
      return;
    }
    if (ROBOT_ID == 1 && station.table == Table::TOP) {
      // Top table is not for bottom robot
      return;
    }

    // Step 1: get on center tape
    if (yPosition != YPosition::TAPE) {
      Drivetrain::backUpToTape();
    }
    // delay(500);

    // Step 2: face the right direction
    FacingDirection desiredFacingDirection = (station.position > position) ? FacingDirection::RIGHT : FacingDirection::LEFT;
    turnToFace(desiredFacingDirection);
    // delay(500);

    // Step 3: drive to the station X position
    if (!Utils::isEqual(station.position, position)) {
      Drivetrain::tapeFollow(abs(station.position - position));
    }
    position = station.position;
    // delay(500);

    // Step 4: face the station
    YPosition stationYPosition = (station.table == Table::TOP || (station.table == Table::MIDDLE && ROBOT_ID == 1)) ? YPosition::TOP : YPosition::BOTTOM;
    desiredFacingDirection = (stationYPosition == YPosition::TOP) ? FacingDirection::TOP : FacingDirection::BOTTOM;
    turnToFace(desiredFacingDirection);    
    // delay(500);

    // Step 5: drive to the station
    Drivetrain::driveUpToTable();
    yPosition = stationYPosition;
  }

  void turnToFace(FacingDirection newFacingDirection) {
    int facingDirectionInt = facingDirectionToInt(facingDirection);
    int newFacingDirectionInt = facingDirectionToInt(newFacingDirection);
    int directionDiff = (newFacingDirectionInt - facingDirectionInt + 4) % 4;
    switch (directionDiff) {
      case 0:
        break;
      case 1:
        Drivetrain::turnUntilTape(TurnDirection::RIGHT);
        break;
      case 2:
        Drivetrain::turnUntilTape(TurnDirection::RIGHT);
        Drivetrain::turnUntilTape(TurnDirection::RIGHT);
        break;
      case 3:
        Drivetrain::turnUntilTape(TurnDirection::LEFT);
        break;
    }
    facingDirection = newFacingDirection;
  }

  int facingDirectionToInt(FacingDirection facingDirection) {
    switch (facingDirection) {
      case FacingDirection::TOP:
        return 0;
      case FacingDirection::RIGHT:
        return 1;
      case FacingDirection::BOTTOM:
        return 2;
      case FacingDirection::LEFT:
        return 3;
    }
    return 0;
  }
}