
function myname( e )
    print( "I am an Entity and my name is " ..  e:name() )
end

function bounce( e )
    mov = e:getMovement()
    pos = e:getPosition()
    
    x, y = pos:get()
    dx, dy = mov:get();
    
    if (x >= 480 and dx > 0) then
        dx = -dx;
    end
    if (x <= 0 and dx < 0) then
        dx = -dx;
    end
    if (y >= 640 and dy > 0) then
        dy = -dy
    end
    if (y <= 0 and dy < 0) then
        dy = -dy
    end
    
    mov:set(dx, dy);
end
