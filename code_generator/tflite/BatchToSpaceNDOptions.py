# automatically generated by the FlatBuffers compiler, do not modify

# namespace: tflite

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class BatchToSpaceNDOptions(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsBatchToSpaceNDOptions(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = BatchToSpaceNDOptions()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def BatchToSpaceNDOptionsBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x54\x46\x4C\x33", size_prefixed=size_prefixed)

    # BatchToSpaceNDOptions
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

def BatchToSpaceNDOptionsStart(builder): builder.StartObject(0)
def BatchToSpaceNDOptionsEnd(builder): return builder.EndObject()
