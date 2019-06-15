from django.db import models

# Create your models here.

class State(models.Model):
    pressure = models.FloatField()
    total = models.FloatField()

    @staticmethod
    def get_state():
        data = None
        try:
            state = State.objects.all()[0]
            print(state)

            data = {'pressure': state.pressure,
                    'total': state.total
                    }
            print(data) 

        except Exception as e:
            print(str(e))
            return {}
        return data
 
    @staticmethod
    def mobileApp():
        data = None
        try:
            state = State.objects.all()[0]
            print(state)

            data = {'pressure': state.pressure,
                    'total': state.total}
            print(data)

        except Exception as e:
            print(str(e))
            return {}
        return data

    @staticmethod
    def saveState(pres, tot):
        try:
            State.objects.all().delete()
            new = State()
            new.pressure = pres
            new.total = tot
            new.save()
           # print(State.objects.all()[0])
        except Exception as e:
            print(str(e))
            return False
        return True

