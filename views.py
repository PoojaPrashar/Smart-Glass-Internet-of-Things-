from django.shortcuts import render
from glass.models import State
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt

import json
# Create your views here.

@csrf_exempt
def index(request):
    return render(request, 'index.html')

def getState(request):
    result =  State.get_state()
    #print("from result", result["temp"])
   
    if (result['pressure'] < 15.0) :
        display_msg= "Fill water"
    else:
        display_msg= "ALL OK"

    context = {
    'pressure' : result['pressure'],
    'total' : result['total'],
    'display_msg' : display_msg,
        }
 
    return render(request,'dashboard.html', context=context)
    #return JsonResponse(State.get_state())

def mobileApp(request):
    return JsonResponse(State.get_state())


def saveState(request, pres, tot):
    # temp = float(request.POST.get('temp'))
    created = State.saveState(float(pres), float(tot))
    return JsonResponse({"success": created})
