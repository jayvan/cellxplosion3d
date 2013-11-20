rootnode = gr.node('root')
rootnode:rotate('x', 90)
rootnode:rotate('y', 90)

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.27451, 0.509804, 0.705882}, {0.27451, 0.509804, 0.705882}, 10)
green = gr.material({0.0, .6, 0.3}, {0.1, 0.6, 0.3}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
grey = gr.material({0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}, 10)
pink = gr.material({1.0, 0.752941, 0.796078}, {1.0, 0.752941, 0.796078}, 10)
yellow = gr.material({1.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 25)

torso = gr.sphere('torso')
rootnode:add_child(torso)
torso:set_material(green)
torso:scale(2.2, 2.0, 1.8);
torso:translate(0.0, 0.05, 0.0)
torso:rotate('x', 90);

shoulders = gr.joint('shoulders', {0, 0, 0}, {-15, 0, 15})
rootnode:add_child(shoulders)
shoulders:translate(0.0, 1.5, 0.0)

upper_torso = gr.sphere('upper_torso')
shoulders:add_child(upper_torso)
upper_torso:set_material(green)
upper_torso:scale(1.5, 0.3, 0.50);

-- HEAD STARTS HERE
neck = gr.joint('neck', {-25.0, 0.0, 15.0}, {-45.0, 0.0, 45.0})
neck:translate(0.0, 1.4, 0.0)
shoulders:add_child(neck)

head = gr.sphere('head')
neck:add_child(head)
head:set_material(pink)
head:scale(0.75, 1.20, 0.75)

left_eye = gr.sphere('left_eye')
neck:add_child(left_eye)
left_eye:set_material(white)
left_eye:translate(0.35, 0.25, 0.6)
left_eye:scale(0.1, 0.1, 0.1)

right_eye = gr.sphere('right_eye')
neck:add_child(right_eye)
right_eye:set_material(white)
right_eye:translate(-0.35, 0.25, 0.6)
right_eye:scale(0.1, 0.1, 0.1)

-- Right ARM

rightShoulder = gr.joint('rightshoulder', {-180.0, 0.0, 90.0}, {0.0, 0.0, 0.0})
rightShoulder:translate(-2.0, -0.50, 0.0)
rightShoulder:rotate('z', -10)
rightShoulder:rotate('x', -90)
shoulders:add_child(rightShoulder)

rightarm = gr.sphere('rightarm')
rightShoulder:add_child(rightarm)
rightarm:set_material(green)
rightarm:translate(0.0, -0.8, 0.0)
rightarm:scale(0.5, 1.0, 0.5)

rightElbow = gr.joint('rightElbow', {-160.0, 0.0, 0.0}, {0.0, 0.0, 0.0})
rightElbow:translate(0.0, -1.8, 0.0)
rightShoulder:add_child(rightElbow)

rightForearm = gr.sphere('rightForearm')
rightElbow:add_child(rightForearm)
rightForearm:set_material(pink)
rightForearm:translate(0.0, -0.9, 0.0)
rightForearm:scale(0.45, 1.0, 0.45)

rightWrist = gr.joint('rightElbow', {-45.0, 0.0, 90.0}, {0.0, 0.0, 0.0})
rightWrist:translate(0.0, -1.8, 0.0)
rightElbow:add_child(rightWrist)

rightHand = gr.sphere('rightHand')
rightWrist:add_child(rightHand)
rightHand:set_material(pink)
rightHand:translate(0.0, -0.2, 0.0)
rightHand:scale(0.3, 0.3, 0.3)

leftShoulder = gr.joint('leftshoulder', {-180.0, 0.0, 90.0}, {0.0, 0.0, 0.0})
leftShoulder:translate(2.0, -0.50, 0.0)
leftShoulder:rotate('z', 10)
leftShoulder:rotate('x', -90)
shoulders:add_child(leftShoulder)

leftarm = gr.sphere('leftarm')
leftShoulder:add_child(leftarm)
leftarm:set_material(green)
leftarm:translate(0.0, -0.8, 0.0)
leftarm:scale(0.5, 1.0, 0.5)

leftElbow = gr.joint('leftElbow', {-160.0, 0.0, 0.0}, {0.0, 0.0, 0.0})
leftElbow:translate(0.0, -1.8, 0.0)
leftShoulder:add_child(leftElbow)

leftForearm = gr.sphere('leftForearm')
leftElbow:add_child(leftForearm)
leftForearm:set_material(pink)
leftForearm:translate(0.0, -0.9, 0.0)
leftForearm:scale(0.45, 1.0, 0.45)

leftWrist = gr.joint('leftElbow', {-45.0, 0.0, 90.0}, {0.0, 0.0, 0.0})
leftWrist:translate(0.0, -1.8, 0.0)
leftElbow:add_child(leftWrist)

leftHand = gr.sphere('leftHand')
leftWrist:add_child(leftHand)
leftHand:set_material(pink)
leftHand:translate(0.0, -0.2, 0.0)
leftHand:scale(0.3, 0.3, 0.3)

-- LEGS ARE HERE

hip_joint = gr.joint('hip_joint', {0, 0, 0}, {-15, 0, 15})
rootnode:add_child(hip_joint)
hip_joint:translate(0.0, -1.2, 0.0)

hips= gr.sphere('hips')
hip_joint:add_child(hips)
hips:set_material(green)
hips:scale(1.5, 0.3, 0.50);

righthip = gr.joint('righthip', {-85.0, 0.0, 45.0}, {0.0, 0.0, 0.0})
righthip:translate(-1.0, -0.10, 0.0)
hip_joint:add_child(righthip)

rightThigh = gr.sphere('rightThigh')
righthip:add_child(rightThigh)
rightThigh:set_material(green)
rightThigh:translate(0.0, -0.8, 0.0)
rightThigh:scale(0.7, 1.0, 0.7)

rightKnee = gr.joint('rightKnee', {0.0, 0.0, 150.0}, {0.0, 0.0, 0.0})
rightKnee:translate(0.0, -1.8, 0.0)
righthip:add_child(rightKnee)

rightShin = gr.sphere('rightShin')
rightKnee:add_child(rightShin)
rightShin:set_material(pink)
rightShin:translate(0.0, -0.9, 0.0)
rightShin:scale(0.6, 1.0, 0.6)

rightAnkle = gr.joint('rightAnkle', {0.0, -90.0, -20.0}, {0.0, 0.0, 0.0})
rightAnkle:translate(0.0, -1.9, 0.0)
rightKnee:add_child(rightAnkle)

rightFoot = gr.sphere('rightFoot')
rightAnkle:add_child(rightFoot)
rightFoot:set_material(pink)
rightFoot:translate(0.0, -0.4, 0.0)
rightFoot:scale(0.4, 0.8, 0.3)

lefthip = gr.joint('lefthip', {-85.0, 0.0, 45.0}, {0.0, 0.0, 0.0})
lefthip:translate(1.0, -0.10, 0.0)
hip_joint:add_child(lefthip)

leftThigh = gr.sphere('leftThigh')
lefthip:add_child(leftThigh)
leftThigh:set_material(green)
leftThigh:translate(0.0, -0.8, 0.0)
leftThigh:scale(0.7, 1.0, 0.7)

leftKnee = gr.joint('leftKnee', {0.0, 0.0, 150.0}, {0.0, 0.0, 0.0})
leftKnee:translate(0.0, -1.8, 0.0)
lefthip:add_child(leftKnee)

leftShin = gr.sphere('leftShin')
leftKnee:add_child(leftShin)
leftShin:set_material(pink)
leftShin:translate(0.0, -0.9, 0.0)
leftShin:scale(0.6, 1.0, 0.6)

leftAnkle = gr.joint('leftAnkle', {.0, -90.0, -20.0}, {0.0, 0.0, 0.0})
leftAnkle:translate(0.0, -1.9, 0.0)
leftKnee:add_child(leftAnkle)

leftFoot = gr.sphere('leftFoot')
leftAnkle:add_child(leftFoot)
leftFoot:set_material(pink)
leftFoot:translate(0.0, -0.4, 0.0)
leftFoot:scale(0.4, 0.8, 0.3)

return rootnode
