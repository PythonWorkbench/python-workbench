class PWB:
    def __init__(self, msg: str):
        self.msg = msg
        print('PWB constructor with msg:', self.msg)

    def getMsg(self):
        return self.msg
