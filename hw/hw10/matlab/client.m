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
port = '/dev/ttyUSB0'
% Opening COM connection
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

fprintf('Opening port %s....\n',port);

% settings for opening the serial port. baud rate 230400, hardware flow control
% wait up to 120 seconds for data before timing out
mySerial = serial(port, 'BaudRate', 230400, 'Timeout',120); 
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
    fprintf('     e: Reset Encoder            f: Set PWM (-100 to 100)\n'); 
    fprintf('     g: Set Current Gain         h: Get Current Gain\n');
    fprintf('     i: Set Position Gain        j: Get Position Gain\n');
    fprintf('     k: Test Current Gain        l: Go to angle (deg)\n');
    fprintf('     r: Get mode                 p: Unpower Motor\n');
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
            fprintf('\nADC current: %d counts\n',n);     % print it to the screen
            
        case 'b'
            % read current mA
            current = fscanf(mySerial,'%d');
            fprintf('\nADC current: %d mA\n',current);    
            
        case 'c'
            counts = fscanf(mySerial,'%d');
            fprintf('\nMotor angle: %d counts.\n',counts);
            
        case 'd'
            % read encoder degrees
            degrees = fscanf(mySerial,'%d');
            fprintf('\nMotor angle: %d degrees.\n',degrees);
        
        case 'e'
            % read encoder degrees
            fprintf('\nEncoder Reset\n');   
            
        case 'f'
            % send PWM
            duty_cycle = input('\nEnter Duty cycle [-100 to 100]\n');
            fprintf(mySerial,'%d\n',duty_cycle);
            
        case 'g'
            % set current gain
            kI = input('\nSet Current Gains\n');
            fprintf(mySerial,'%d\n',kI);
            
        case 'h'
            % get current gain
            kI2= fscanf(mySerial,'%f');
            fprintf('%d\n',kI2);
            
        case 'i'
            % set position gain
            kP = input('\nSet Position Gain\n');
            fprintf(mySerial,'%d\n',kP);  
            
        case 'j'
            % set position gain
            kP2 = fscanf(mySerial,'%f');
            fprintf(mySerial,'%d\n',kI);
            
        case 'k'
            % test current gain
            data = read_plot_matrix(mySerial);            
            
        case 'n'                         % example operation
            n = input('Enter number: '); % get the number to send
            fprintf(mySerial, '%d\n',n); % send the number
            n = fscanf(mySerial,'%d');   % get the incremented number back
            fprintf('Read: %d\n',n);     % print it to the screen
        
        case 'p'                         
            mode = fscanf(mySerial,'%c');
            fprintf('%c',mode);
           
        case 'r'                        
            mode = fscanf(mySerial,'%c');
            fprintf('%c',mode);
        
        case 'q'
            has_quit = true;             % exit client
        
        case 'x'
            a = input('Enter number: '); % get the number to send
            fprintf(mySerial, '%d\n', a); % send the numbers
            b = input('Enter number: '); % get the number to send
            fprintf(mySerial, '%d\n', b); % send the numbers
            n = fscanf(mySerial,'%d');   % get the incremented number back
            fprintf('Read: %d\n',n);     % print it to the screen
        
        otherwise
            fprintf('Invalid Selection %c\n', selection);
    end
end

end