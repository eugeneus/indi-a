 
local physics = require("physics")
local trajapi = require("trajectorylib")
local mathapi = require("mathlib")
 
physics.start()
physics.setGravity(0,10)
 
local path = nil
 
 
--[[ environment setup ]]--
 
local start, sling = nil, nil
local offsetX, offsetY = 50, 300
local iteration = 0.1 -- gap between increments of trajectory points
 
 
--[[ trajectory plotting ]]--
 
function trajectory( start, velocity, angle, iteration, untiloffscreen )
        if (path) then path:removeSelf(); end
        path = display.newGroup()
        
        local flightmultiple = 1
        if (untiloffscreen) then
                flightmultiple = 2
        end
    local points, r, h, f = trajapi.calcTrajectoryPoints( 0, 0, velocity, angle, iteration, flightmultiple )
    
    print( 'angle: ', angle )
    print( 'velocity: ', velocity )
    print( 'range: ', r )
    print( 'height: ', h )
    print( 'flight time: ', f )
    
    for i=1, #points do
            local radius = (points[i].velocityx + points[i].velocityy) * 0.1
            if (radius < 2) then
                    radius = 2
            end
            display.newCircle( path, start.x + points[i].x, start.y - points[i].y, radius )
    end
    
    return points
end
 
 
--[[ throwing the ball ]]--
function throw( points, sling, start, distance, angle )
        local radius = 30
        local ball = display.newCircle( path, start.x, start.y, radius )
        ball.alpha = .7
        ball:setFillColor( 90,90,200 )
        physics.addBody( ball, "dynamic", {friction=.1, bounce=.1, density=1, radius=radius } )
        
        local point = points[2]
        local area = trajapi.calcAreaOfCircle( radius )
        local density = 1
        local mass = density * area
        local g = 2.1
        print('area: '..area)
        print('mass: '..mass)
        print('dist: '.. distance)
        
        local ax, ay = points[1].velocityx, points[1].velocityy
        local fx = mass*ax
        local fy = mass*ay
        local ratio = 100 * 1.62 -- MAGIC VALUE
        print('velocity: '..points[2].velocityx, points[2].velocityy)
        print('force: '..fx,fy)
        print('time: '..points[2].time)
        ball:applyForce( fx/ratio, -fy/ratio )
        
        function ball:timer(event)
                timer.cancel( ball.t )
                Runtime:removeEventListener("enterFrame", ball)
                ball:removeSelf()
        end
        ball.t = timer.performWithDelay(8000, ball, 1)
        
        function ball:enterFrame(event)
                local c = display.newCircle(path, ball.x, ball.y,3)
                c:setFillColor(255,0,0)
        end
        Runtime:addEventListener("enterFrame", ball)
end
 
 
--[[ initial point capture ]]--
 
function touch(event)
        if (not start) then
                start = event
                display.newCircle( event.x, event.y, 2 )
        elseif (not sling) then
                sling = event
                display.newCircle( event.x, event.y, 2 )
                local c = display.newCircle( start.x, start.y, mathapi.lengthOf( start, sling ) )
                c:setStrokeColor( 0,0,255 )
                c:setFillColor( 0,0,0,0 )
                c.strokeWidth = 2
                
                local angle = math.abs( mathapi.angleOf( sling, start ) )
                local distance = mathapi.lengthOf( sling, start )
                local points = trajectory( start, distance, angle, iteration )
                throw( points, sling, start, distance, angle )
        end
end
 
 
Runtime:addEventListener("tap", touch)
 
local control = display.newGroup()
local sphere, line, dot, track = nil, nil, nil, nil
 
function drag( event )
        if (event.phase == "began") then
                if (dot) then dot:removeSelf(); end
                dot = display.newCircle( control, event.x, event.y, 4 )
                dot:setFillColor(255, 0, 0)
        elseif (event.phase == "moved") then
                local len = mathapi.lengthOf( dot, event )
                if (sphere) then sphere:removeSelf(); end
                if (track) then track:removeSelf(); end
                if (line) then line:removeSelf(); end
                sphere = display.newCircle( control, dot.x, dot.y, len )
                dot:removeSelf()
                dot = display.newCircle( control, sphere.x, sphere.y, 4 )
                dot:setFillColor(255, 0, 0)
                track = display.newCircle( control, event.x, event.y, 25 )
                track:setFillColor( 0, 255, 0 )
                line = display.newLine( control, sphere.x, sphere.y, event.x, event.y )
                line.width = 2
                line:setColor( 0, 0, 255 )
        else
                control.alpha = .5
                
        local angle = math.abs( mathapi.angleOf( event, dot ) )
        local distance = mathapi.lengthOf( event, dot )
        local points = trajectory( dot, distance, angle, iteration, true )
        throw( points, event, dot, distance, angle )
        end
        return true     
end
 
Runtime:addEventListener( "touch", drag )