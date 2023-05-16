# Flight-Reservation-System
Developed a terminal based application using OOP concepts namely New-PAK Airline Flight System (NPAFS) for a newly established airline. Major features are login/signup, managing flight schedule, managing passengers, booking facility and payment.

A menu is provided to navigate the full system. After completion of each step users are 
provided with a menu to the subsequent process and a link to main menu

Login Panel 

Admin Panel: NPAFS has a team to manage the interaction with the system. The team  members can login to change the schedule of          flights. Add new routes for local and international flights. Restrict the number of passengers in a plane. Update airline inquiry details. 

Passenger Panel: Users are the passengers that use to travel using NPAFS. A new user can register in the system with a valid CNIC. An   adult passenger can also register for the dependents under 18. 
  
Registration details are stored in two separate files namely Admin.txt and Passengers.txt. These files have Usernames and Passwords. User can also reset the password and username. The registration process hides the password and only shows ******** instead of actual entered characters. New user must re-enter the password and system verify any typing mistake. Password must be 8 characters long and use of minimum one special character, uppercase, lowercase, and numeric digit is must. The passenger account is only created if a valid 13-digit CNIC is provided and CNIC must not be repeated in existing record. Otherwise, appropriate messages should be generated to notify the users. Usersprovide their basic identification details to register.

Maintains a flight Schedule. Arrival and Departure Time is displayed for each flight. Current available seats are regularly updated and displayed in the information panel. 

Booking 

Passengers book a flight by providing and considering the following information:
-> Selecting the country and destination airport details. 
-> Reserving a seat by considering the current available seats and schedule of flights. 
-> Route details for direct and indirect flights. 
-> Costs are provided for each available flight by overloaded stream operator.

Any user can search the available flights and timing details. Only a registered passenger can reserve a seat. Passengers can update their details. Change their scheduled flight or even cancel it with a penalty of 25% actual payment. 

Payment

The payment details for each booked flight are recorded. Ticket price for all journeys is displayed to the users. 

-> One hour travel costs Rs.10,000 for a local flight and Rs.20,000 for international flights. 
-> Government deducts 5% and 10% tax on local and international flights, respectively.
-> A route from a country A to B can have C etc. in between, therefore the cost for a flight depends on the route. 




