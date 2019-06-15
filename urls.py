
from django.urls import path, include
from django.contrib import admin
from django.views.decorators.csrf import csrf_exempt

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('restaurant/', views.getState, name='state'),
    path('health/', views.mobileApp, name='mobile'),
    path('savestate/<str:pres>/<str:tot>', csrf_exempt(views.saveState), name='save'),
]

