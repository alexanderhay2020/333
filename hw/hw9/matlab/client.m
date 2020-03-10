function client(port)
%   provides a menu for accessing PIC32 motor control functions
%
%   client(port)
%
%   Input Arguments:
%       port - the name of the com port.  This should be the same as what
%               you use in screen or putty in quotes ' '
%
%   Example:
%       client('/dev/ttyUSB0') (Linux/Mac)
%       client('COM3') (PC)
%
%   For convenience, you may want to change this so that the port is hardcoded.
port = '/dev/ttyUSB1'
% Opening COM connection
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

fprintf('Opening port %s....\n',port);

% settings for opening the serial port. baud rate 230400, hardware flow control
% wait up to 120 seconds for data before timing out
mySerial = serial(port, 'BaudRate', 230400, 'FlowControl', 'hardware','Timeout',120); 
% opens serial connection
fopen(mySerial);
% closes serial port when function exits
clean = onCleanup(@()fclose(mySerial));                                 

has_quit = false;
% menu loop
while ~has_quit
    fprintf('PIC32 MOTOR DRIVER INTERFACE\n\n');
    % display the menu options; this list will grow
    fprintf('     a: Read Current (counts)    b: Read Current (mA)\n');
    fprintf('     c: Read Encoder (counts)    d: Read Encoder (deg)\n');
    fprintf('     e: Reset Encoder\n');    
    fprintf('     q: Quit                     x: Test\n');
    % read the user's choice
    selection = input('\nENTER COMMAND: ', 's');
     
    % send the command to the PIC32
    fprintf(mySerial,'%c\n',selection);
    
    % take the appropriate action
    switch selection
        case 'a'
            % read current ADC counts
            n = fscanf(mySerial,'%d');   % get the ADC count
            fprintf('Read: %d\n',n);     % print it to the screen
            
        case 'b'
            % read encoder counts
            fprintf('prompt\n');    
            
        case 'c'
            counts = fscanf(mySerial,'%d');
            fprintf('\nThe motor angle is %d counts.\n',counts);
            
        case 'd'
            % read encoder degrees
            degrees = fscanf(mySerial,'%d');
            fprintf('\nThe motor angle is %d degrees.\n',degrees);
        
        case 'e'
            % read encoder degrees
            fprintf('\nEncoder Reset\n');            
            
        case 'n'                         % example operation
            n = input('Enter number: '); % get the number to send
            fprintf(mySerial, '%d\n',n); % send the number
            n = fscanf(mySerial,'%d');   % get the incremented number back
            fprintf('Read: %d\n',n);     % print it to the screen
        
        case 'q'
            has_quit = true;             % exit client
        
        case 'x'
            a = input('Enter number: '); % get the number to send
            b = input('Enter number: '); % get the number to send
            fprintf(mySerial, '%d\n', a); % send the numbers
            fprintf(mySerial, '%d\n', b); % send the numbers
            n = fscanf(mySerial,'%d');   % get the incremented number back
            fprintf('Read: %d\n',n);     % print it to the screen
        
        otherwise
            fprintf('Invalid Selection %c\n', selection);
    end
end

end