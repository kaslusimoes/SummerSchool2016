"""
Evaluates if, with a sigmoid function probability, a phenotype *fx* invades another agent *fy*
"""
function sigInvades(fx::Float64, fy::Float64)
     ey = e^(- β * fy)
     pmax = ey + e^(- β * fx)
     ey*rand() < pmax ? return true : false
end

"""
Evaluates the fitness of an agent *ag* of a Society *soc*
"""
function fitness(ag::Int32, soc::Society)
     defec = soc[ag].defect
     for i in soc[ag].neigh
       # do something
     end
end