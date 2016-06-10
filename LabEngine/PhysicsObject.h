

class PhysicsObject
{
public:

    double x;
    double y;
    double z;

    double velocityX;
    double velocityY;
    double velocityZ;

    double mass;

    double collideCounter;

    PhysicsObject();
    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    double getZ() const;
    void setZ(double value);
    double getVelocityX() const;
    void setVelocityX(double value);
    double getVelocityY() const;
    void setVelocityY(double value);
    double getVelocityZ() const;
    void setVelocityZ(double value);
    double getMass() const;
    void setMass(double value);
    double getCollideCounter() const;
    void setCollideCounter(double value);
};

double PhysicsObject::getX() const
{
    return x;
}

void PhysicsObject::setX(double value)
{
    x = value;
}

double PhysicsObject::getY() const
{
    return y;
}

void PhysicsObject::setY(double value)
{
    y = value;
}

double PhysicsObject::getZ() const
{
    return z;
}

void PhysicsObject::setZ(double value)
{
    z = value;
}

double PhysicsObject::getVelocityX() const
{
    return velocityX;
}

void PhysicsObject::setVelocityX(double value)
{
    velocityX = value;
}

double PhysicsObject::getVelocityY() const
{
    return velocityY;
}

void PhysicsObject::setVelocityY(double value)
{
    velocityY = value;
}

double PhysicsObject::getVelocityZ() const
{
    return velocityZ;
}

void PhysicsObject::setVelocityZ(double value)
{
    velocityZ = value;
}

double PhysicsObject::getMass() const
{
    return mass;
}

void PhysicsObject::setMass(double value)
{
    mass = value;
}

double PhysicsObject::getCollideCounter() const
{
    return collideCounter;
}

void PhysicsObject::setCollideCounter(double value)
{
    collideCounter = value;
}
