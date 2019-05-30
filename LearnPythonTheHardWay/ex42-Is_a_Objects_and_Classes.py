## Animal is-a object (yes, sort of confusing) look at the extra credit
class Animal(object):
    pass


## Dog is an animal
class Dog(Animal):
    def __init__(self, name):
        ## init name
        self.name = name


## Cat is an Animal
class Cat(Animal):
    def __init__(self, name):
        ## ??
        self.name = name


## Person class
class Person(object):
    def __init__(self, name):
        ## init name
        self.name = name
        ## Person has-a pet of some kind
        self.pet = None


## Employee is a kind of person
class Employee(Person):
    def __init__(self, name, salary):
        ## ?? hmm what is this strange magic?
        ## init the parent class
        super(Employee, self).__init__(name)
        ## init the money
        self.salary = salary


## Fish class
class Fish(object):
    pass


## Salmon is kind of fish
class Salmon(Fish):
    pass


## Halibut is kind of fish
class Halibut(Fish):
    pass


## rover is-a dog
rover = Dog("Rover")
## cat instance
satan = Cat("Satan")
## person instance
mary = Person("Mary")
## person's pet init
mary.pet = satan
## employee instance
frank = Employee("Frank", 120000)
## employee's pet
frank.pet = rover
## fish instane
flipper = Fish()
## salmon instance
crouse = Salmon()
## halibut
harry = Halibut()
