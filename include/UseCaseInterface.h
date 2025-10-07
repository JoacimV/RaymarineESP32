#ifndef USECASEINTERFACE_H
#define USECASEINTERFACE_H

/**
 * Abstract base class for use cases
 * Defines a generic interface for use cases with input and output types.
 * This is an abstract class that cannot be instantiated directly.
 */
template <typename Input, typename Output>
class UseCase
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~UseCase() = default;

    // Pure virtual method - must be implemented by derived classes
    virtual Output apply(Input param) = 0;

protected:
    // Protected constructor to prevent direct instantiation
    UseCase() = default;

private:
    // Delete copy constructor and assignment operator to prevent copying
    UseCase(const UseCase&) = delete;
    UseCase& operator=(const UseCase&) = delete;
};

/**
 * Specialization for void input (no parameters)
 * Abstract class for use cases that don't require input parameters
 */
template <typename Output>
class UseCase<void, Output>
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~UseCase() = default;

    // Pure virtual method - must be implemented by derived classes
    virtual Output apply() = 0;

protected:
    // Protected constructor to prevent direct instantiation
    UseCase() = default;

private:
    // Delete copy constructor and assignment operator to prevent copying
    UseCase(const UseCase&) = delete;
    UseCase& operator=(const UseCase&) = delete;
};

/**
 * Specialization for void output (no return value)
 * Abstract class for use cases that don't return a value
 */
template <typename Input>
class UseCase<Input, void>
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~UseCase() = default;

    // Pure virtual method - must be implemented by derived classes
    virtual void apply(Input param) = 0;

protected:
    // Protected constructor to prevent direct instantiation
    UseCase() = default;

private:
    // Delete copy constructor and assignment operator to prevent copying
    UseCase(const UseCase&) = delete;
    UseCase& operator=(const UseCase&) = delete;
};

/**
 * Specialization for both void input and void output
 * Abstract class for use cases that neither take parameters nor return values
 */
template <>
class UseCase<void, void>
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~UseCase() = default;

    // Pure virtual method - must be implemented by derived classes
    virtual void apply() = 0;

protected:
    // Protected constructor to prevent direct instantiation
    UseCase() = default;

private:
    // Delete copy constructor and assignment operator to prevent copying
    UseCase(const UseCase&) = delete;
    UseCase& operator=(const UseCase&) = delete;
};

#endif // USECASEINTERFACE_H